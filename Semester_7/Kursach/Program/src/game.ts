import {Square, Move, Capture, Field, Choice} from "./algorithm";
import {Value, Color} from "./algorithm";
import {white, black, whiteKing, blackKing, empty} from "./algorithm";
import {ReservedOrUserListener} from "socket.io/dist/typed-events";

export class Game {
    private _field: Field
    private _turn: Color;
    private _continueMove: Square | null;
    private _level: number | null; //Null if it's not ai game

    //_whitePlayer or/and _blackPlayer can be null if it's ai game
    private _whitePlayer: ReservedOrUserListener<any, any, any> | null;
    private _blackPlayer: ReservedOrUserListener<any, any, any> | null;

    constructor(field: Field,
                whitePlayer: ReservedOrUserListener<any, any, any> | null = null,
                blackPlayer: ReservedOrUserListener<any, any, any> | null = null) {
        this._field = field;
        this._turn = white;
        this._continueMove = null; //Not null value means, that checker at this square
                                   //captured opponent checker earlier and can continue to capture
        this._level = null;
        this._whitePlayer = whitePlayer;
        this._blackPlayer = blackPlayer;
    }

    public setLevel(level: number): void {
        this._level = level;
    }

    public getLevel(): number | null {
        return this._level;
    }

    public getField(): Field {
        return this._field;
    }

    public getTurn(): Color {
        return this._turn;
    }

    public switchTurn(): void {
        if (this._turn == white) {
            this._turn = black;
        } else {
            this._turn = white;
        }
    }

    public move(move: Move): void {
        this._field.move(move);
        this.switchTurn();
    }

    public capture(capture: Capture): void {
        this._field.capture(capture);
        let jumpedTo = capture.getMove().getTo();
        if (this._field.getOneMoveCaptures(jumpedTo).length == 0) {
            this.switchTurn();
            this._continueMove = null;
        } else {
            this._continueMove = jumpedTo;
        }
    }

    public apply(choice: Move | Capture) {
        if (choice instanceof Move) {
            this.move(choice);
        } else {
            this.capture(choice);
        }
    }

    public getContinueMove(): Square | null {
        return this._continueMove;
    }

    public getOpponentSocket(selfSocket: ReservedOrUserListener<any, any, any>): ReservedOrUserListener<any, any, any> {
        if (this._whitePlayer == selfSocket) {
            return this._blackPlayer;
        } else {
            return this._whitePlayer;
        }
    }

    public setOwnSocket(color: Color, socket: ReservedOrUserListener<any, any, any>): void {
        if (color == white) {
            this._whitePlayer = socket;
        } else {
            this._blackPlayer = socket;
        }
    }

    public getOwnColor(selfSocket: ReservedOrUserListener<any, any, any>): Color {
        if (this._whitePlayer == selfSocket) {
            return white;
        } else {
            return black;
        }
    }

    //Return winner's color or null if there is no winner yet
    public getWinner(): Color | null {
        let whiteCount = 0;
        let blackCount = 0;
        for (let i = 0; i < 8; i++) {
            for (let j = 0; j < 8; j++) {
                let value = this._field.get(i, j);
                if (value == white || value == whiteKing) {
                    whiteCount++;
                } else if (value == black || value == blackKing) {
                    blackCount++;
                }
            }
        }
        if (whiteCount == 0) {
            return black;
        } else if (blackCount == 0) {
            return white;
        }
        if (whiteCount < 11 && this._turn == white) {
            const captures = this._field.getCaptures(white).length;
            const moves = this._field.getMoves(white).length;
            if (captures + moves == 0) {
                return black;
            }
        }
        else if (blackCount < 11 && this._turn == black) {
            const captures = this._field.getCaptures(black).length;
            const moves = this._field.getMoves(black).length;
            if (captures + moves == 0) {
                return white;
            }
        }
        return null;
    }
}