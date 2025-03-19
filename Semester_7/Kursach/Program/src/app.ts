import {ReservedOrUserListener} from "socket.io/dist/typed-events";
import {Square, Move, Capture, Field, AI, Choice} from "./algorithm";
import {Value, Color} from "./algorithm";
import {white, black, whiteKing, blackKing, empty} from "./algorithm";
import {Game} from "./game";
import { v4 } from 'uuid';

const express = require('express');
const { createServer } = require('node:http');
const { join } = require('node:path');
const { Server } = require('socket.io');

const app = express();
const server = createServer(app);
const io = new Server(server);

app.use(express.static(join(__dirname, '../assets')));
app.set('view engine', 'html');
app.engine('html', require('ejs').renderFile);

app.get('/main', (req: any, res: any) => {
    res.render(join(__dirname, '../assets/views/index.html'));
});

app.get('/info', (req: any, res: any) => {
    res.render(join(__dirname, '../assets/views/info.html'));
});

app.get('/game/pc', (req: any, res: any) => {
    const color = req.query['color'];
    const level = req.query['level'];
    const aiGame = true;
    //On pc game we don't have gameId in request query, so generate it
    const gameId = v4();
    res.render(join(__dirname, '../assets/views/game.html'), {color, level, aiGame, gameId});
})

app.get('/game/multiplayer', (req: any, res: any) => {
    const color = req.query['color'];
    const level = req.query['level'];
    const aiGame = false;
    //On multiplayer game we have gameId in request query,
    //as it was generated earlier, when game was arranged by server
    const gameId = req.query['gameId'];
    res.render(join(__dirname, '../assets/views/game.html'), {color, level, aiGame, gameId});
})

const games: Map<string, Game> = new Map();
const playerQueue: ReservedOrUserListener<any, any, any>[] = [];

const field: Value[][] = [
    ['b', ' ', 'b', ' ', ' ', ' ', 'w', ' '],
    [' ', 'b', ' ', ' ', ' ', 'w', ' ', 'w'],
    ['b', ' ', 'b', ' ', ' ', ' ', 'w', ' '],
    [' ', 'b', ' ', ' ', ' ', 'w', ' ', 'w'],
    ['b', ' ', 'b', ' ', ' ', ' ', 'w', ' '],
    [' ', 'b', ' ', ' ', ' ', 'w', ' ', 'w'],
    ['b', ' ', 'b', ' ', ' ', ' ', 'w', ' '],
    [' ', 'b', ' ', ' ', ' ', 'w', ' ', 'w'],
];

//Poll players in queue and create multiplayer game if 2 players can be extracted
setInterval(() => {
    if (playerQueue.length >= 2) {
        const player1 = playerQueue.shift();
        const player2 = playerQueue.shift();
        const game = new Game(new Field(structuredClone(field)), player1, player2);
        const gameId = v4();
        games.set(gameId, game);
        player1.emit("game-found-event", {color: 'white', level: null, aiGame: false, gameId});
        player2.emit("game-found-event", {color: 'black', level: null, aiGame: false, gameId});
    }
}, 1000);

const mainNamespace = io.of('/main');
const gameNamespace = io.of('/game');

mainNamespace.on('connection', (socket: any) => {
    console.log('a user connected to main');

    socket.on('multiplayer-game-desire-event', (data: any) => {
        const positionInPlayerQueue = playerQueue
            .indexOf(socket);
        if (positionInPlayerQueue == -1) {
            playerQueue.push(socket);
        }
    })

    socket.on('disconnect', (data: any) => {
        console.log('a user disconnected from queue');
        const positionInPlayerQueue = playerQueue
            .indexOf(socket);
        if (positionInPlayerQueue != -1) {
            playerQueue.splice(positionInPlayerQueue, 1);
        }
    })
})

gameNamespace.on('connection', (socket: any) => {
    console.log('a user connected to game');

    socket.on('left-board-click', (data: any) => {
        let picks = JSON.parse(data);
        const currentPick = picks.currentPick ? new Square(picks.currentPick) : null;
        const newPick = new Square(picks.newPick);
        const game: Game = games.get(picks.gameId)!;
        const field: Field = games.get(picks.gameId)!.getField();
        const winner: Color | null = game.getWinner();
        const aiGame = game.getLevel() != null;
        if (winner == null) {
            if (field.getValue(newPick) != empty) {
                const captures = field.getOneMoveCaptures(newPick);
                if (captures.length != 0) {
                    socket.emit('draw-board-marks', JSON.stringify(captures.map(c => c.getMove().getTo().toString())));
                } else {
                    const moves = field.getSquareMoves(newPick);
                    socket.emit('draw-board-marks', JSON.stringify(moves.map(m => m.getTo().toString())));
                }
            } else {
                if (currentPick != null
                    && checkerBelongsToPlayer(field.getValue(currentPick), picks.color)
                    && game.getTurn() == picks.color) {
                    const captures = field.getOneMoveCaptures(currentPick);
                    if (captures.length != 0) {
                        const capture = captures.find(c => c.getMove().getFrom().equals(currentPick)
                            && c.getMove().getTo().equals(newPick));
                        if (capture !== undefined) {
                            game.capture(capture);
                            notifyPlayers(socket, game.getOpponentSocket(socket), capture);
                            //Change this hardcode to make player-2-player game possible and add difficulty set!!!
                            const aiColor = picks.color == white ? black : white;
                            if (aiGame && aiColor == game.getTurn()
                                && game.getWinner() == null) {
                                const ai = new AI(aiColor);
                                const choice = ai.decide(field, game.getLevel()!);
                                game.apply(choice);
                                notifyPlayers(null, socket, choice);
                            }
                        }
                    } else if (field.getCaptures(game.getTurn()).length == 0
                        && checkerBelongsToPlayer(field.getValue(currentPick), picks.color)
                        && game.getTurn() == picks.color) {
                        const moves = field.getSquareMoves(currentPick);
                        const move = moves.find(m => m.getFrom().equals(currentPick)
                            && m.getTo().equals(newPick));
                        if (move !== undefined) {
                            game.move(move);
                            notifyPlayers(socket, game.getOpponentSocket(socket), move);
                            //Change this hardcode to make player-2-player game possible and add difficulty set!!!
                            const aiColor = picks.color == white ? black : white;
                            if (aiGame && aiColor == game.getTurn()
                                && game.getWinner() == null) {
                                const ai = new AI(aiColor);
                                const choice = ai.decide(field, game.getLevel()!);
                                game.apply(choice);
                                notifyPlayers(null, socket, choice);
                            }
                        }
                    }
                }
            }
        }
        if (game.getWinner() != null) {
            const opponentSocket = game.getOpponentSocket(socket);
            socket.emit("game-over-event", JSON.stringify({
                winner: game.getWinner()
            }));
            if (opponentSocket != null) {
                opponentSocket.emit("game-over-event", JSON.stringify({
                    winner: game.getWinner()
                }));
            }
            games.delete(picks.gameId);
        }
    })

    socket.on('game-info-event', (data: any) => {
        const {aiGame, opponentColor, level, gameId} = data;
        if (aiGame === 'true') {
            //Add game is required only for ai game, as
            //color and difficulty obtained from client,
            //whereas in multiplayer game all game parameters
            //are managed by server
            games.set(gameId, new Game(new Field(structuredClone(field))));
            const game = games.get(gameId)!;
            game.setLevel(level);
            if (opponentColor == white) {
                const ai = new AI(white);
                const choice = ai.decide(game.getField(), level);
                game.apply(choice);
                notifyPlayers(null, socket, choice);
            }
        } else {
            const game = games.get(gameId)!;
            if (opponentColor == white) {
                game.setOwnSocket(black, socket);
            } else {
                game.setOwnSocket(white, socket);
            }
        }
    })

    socket.on('disconnect-event', (data: any) => {
        const {gameId} = data;
        const game = games.get(gameId);
        if (game != undefined) {
            const opponentSocket = game.getOpponentSocket(socket);
            if (opponentSocket != null) {
                opponentSocket.emit("game-over-event", JSON.stringify({
                    winner: game.getOwnColor(opponentSocket)
                }));
            }
        }
        games.delete(gameId);
    })

    socket.on('disconnect', (data: any) => {
        console.log('a user disconnected from game');
        const positionInPlayerQueue = playerQueue
            .indexOf(socket);
        if (positionInPlayerQueue != -1) {
            playerQueue.splice(positionInPlayerQueue, 1);
        }
    })
})

function checkerBelongsToPlayer(checker: Value, playerColor: Color) {
    return (checker == playerColor)
        || (checker == whiteKing && playerColor == white)
        || (checker == blackKing && playerColor == black);
}

function notifyPlayers(playerSocket: any | null, opponentSocket: any | null, data: Move | Capture) {
    if (playerSocket) {
        if (data instanceof Move) {
            playerSocket.emit('board-move-event', JSON.stringify(data));
        } else {
            playerSocket.emit('board-capture-event', JSON.stringify(data));
        }
    }
    if (opponentSocket) {
        if (data instanceof Move) {
            opponentSocket.emit('board-move-event', JSON.stringify(data));
        } else {
            opponentSocket.emit('board-capture-event', JSON.stringify(data));
        }
    }
}

server.listen(3000, () => {
    console.log('server running at http://localhost:3000');
});