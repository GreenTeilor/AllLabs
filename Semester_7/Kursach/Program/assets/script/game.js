const socket = io('/game');

socket.on('connect', () => {
    socket.emit('game-info-event', {
        aiGame: document.getElementById('aiGame').innerHTML,
        opponentColor: document.getElementById('opponentColor').innerHTML.substring(0, 1),
        level: document.getElementById('level').innerHTML,
        gameId: document.getElementById('gameId').innerHTML
    });
});

socket.on('disconnect', () => {
    socket.emit('disconnect-event', {
        gameId: document.getElementById('gameId').innerHTML
    });
});

socket.on('game-over-event', (data) => {
    const { winner: winnerColor } = JSON.parse(data);
    showOverlay(playerColor[0] === winnerColor ? "winOverlay" : "defeatOverlay");
})

window.addEventListener('beforeunload', (event) => {
    socket.emit('disconnect-event', {
        gameId: document.getElementById('gameId').innerHTML
    });
});

let blackKingImg = '../images/blackKing.png';
let whiteKingImg = '../images/whiteKing.png';

let currentPick = null;
const boardMarks = [];

const searchParams = new URLSearchParams(window.location.search);
const playerColor = searchParams.get('color').slice(0, 1);

socket.on('draw-board-marks', (data) => {
    const squares = JSON.parse(data);
    console.log(squares);
    boardMarks.forEach(bm => {
        document.getElementById(bm).innerHTML = '';
    })
    boardMarks.length = 0;
    squares.forEach(square => {
        boardMarks.push(square);
        const mark = document.createElement("div");
        mark.classList.add("circle");
        const element = document.getElementById(square);
        element.appendChild(mark);
    })
});

socket.on('board-capture-event', (data) => {
    console.log(data);
    boardMarks.forEach(bm => {
        document.getElementById(bm).innerHTML = '';
    })
    boardMarks.length = 0;
    const capture = JSON.parse(data);
    const fromElem = document.getElementById(capture.move.from);
    const toElem = document.getElementById(capture.move.to);
    const checker = fromElem.innerHTML;
    fromElem.innerHTML = '';
    if (checker.includes('white') && capture.isBecameKing) {
        toElem.innerHTML = `<img src=\"${whiteKingImg}\">`;
    } else if (checker.includes('black') && capture.isBecameKing) {
        toElem.innerHTML = `<img src=\"${blackKingImg}\">`;
    } else {
        toElem.innerHTML = checker;
    }
    capture.squareToClear.forEach(s => {
        document.getElementById(s).innerHTML = '';
    });
})

socket.on('board-move-event', (data) => {
    console.log(data);
    boardMarks.forEach(bm => {
        document.getElementById(bm).innerHTML = '';
    })
    boardMarks.length = 0;
    const move = JSON.parse(data);
    const fromElem = document.getElementById(move.from);
    const toElem = document.getElementById(move.to);
    const checker = fromElem.innerHTML;
    fromElem.innerHTML = '';
    if (checker.includes('white') && move.isBecameKing) {
        toElem.innerHTML = `<img src=\"${whiteKingImg}\">`;
    } else if (checker.includes('black') && move.isBecameKing) {
        toElem.innerHTML = `<img src=\"${blackKingImg}\">`;
    } else {
        toElem.innerHTML = checker;
    }
})

function showOverlay(id) {
    const overlay = document.getElementById(id);
    overlay.classList.remove('hidden');
}

function handleClick(id) {
    const gameId = document.getElementById('gameId').innerHTML;
    const event = new LeftClickEvent(currentPick, id, playerColor, gameId);
    socket.emit('left-board-click', JSON.stringify(event));
    currentPick = id;
}

function handleRightClick(id) {
    alert("rightClick");
}

class LeftClickEvent {
    constructor(currentPick, newPick, playerColor, gameId) {
        this.currentPick = currentPick;
        this.newPick = newPick;
        this.color = playerColor;
        this.gameId = gameId;
    }
}

Array.from(document.querySelectorAll("div"))
    .filter(element => {
        return element.getAttribute("class").includes("white")
            || element.getAttribute("class").includes("black");
    })
    .forEach(element => {
        element.addEventListener('click', () => {
            handleClick(element.id);
        });
        element.addEventListener('contextmenu', (event) => {
            event.preventDefault();
            handleRightClick(element.id);
        })
    });