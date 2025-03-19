export const white = 'w';
export const black = 'b';
export const whiteKing = 'W';
export const blackKing = 'B';
export const empty = ' ';
export type Value = typeof white
    | typeof black
    | typeof whiteKing
    | typeof blackKing
    | typeof empty;

export type Color = typeof white
    | typeof black;

enum SquareLetter { H, G, F, E, D, C, B, A }
enum SquareNumber { _8, _7, _6, _5, _4, _3, _2, _1 }

export const letterMap = new Map<string, SquareLetter>([
    ['A', SquareLetter.A],
    ['B', SquareLetter.B],
    ['C', SquareLetter.C],
    ['D', SquareLetter.D],
    ['E', SquareLetter.E],
    ['F', SquareLetter.F],
    ['G', SquareLetter.G],
    ['H', SquareLetter.H]
]);

export const reverseLetterMap = new Map<SquareLetter, string>([
    [SquareLetter.A, 'A'],
    [SquareLetter.B, 'B'],
    [SquareLetter.C, 'C'],
    [SquareLetter.D, 'D'],
    [SquareLetter.E, 'E'],
    [SquareLetter.F, 'F'],
    [SquareLetter.G, 'G'],
    [SquareLetter.H, 'H']
]);

export const numberMap = new Map<string, SquareNumber>([
    ['1', SquareNumber._1],
    ['2', SquareNumber._2],
    ['3', SquareNumber._3],
    ['4', SquareNumber._4],
    ['5', SquareNumber._5],
    ['6', SquareNumber._6],
    ['7', SquareNumber._7],
    ['8', SquareNumber._8]
]);

export const reverseNumberMap = new Map<SquareNumber, string>([
    [SquareNumber._1, '1'],
    [SquareNumber._2, '2'],
    [SquareNumber._3, '3'],
    [SquareNumber._4, '4'],
    [SquareNumber._5, '5'],
    [SquareNumber._6, '6'],
    [SquareNumber._7, '7'],
    [SquareNumber._8, '8']
]);

export class Square {
    private _letter: SquareLetter;
    private _number: SquareNumber;

    constructor(square: string);
    constructor(squareLetter: SquareLetter, squareNumber: SquareNumber);
    constructor(...args: any[]) {
        if (args.length == 1) {
            let square: string = args[0];
            let chars = square.split("");
            this._letter = letterMap.get(chars[0]);
            this._number = numberMap.get(chars[1]);
        } else if (args.length == 2) {
            let squareLetter: SquareLetter = args[0];
            let squareNumber: SquareNumber = args[1];
            this._letter = squareLetter;
            this._number = squareNumber;
        }
    }

    public getLetter(): SquareLetter {
        return this._letter;
    }

    public getNumber(): SquareNumber {
        return this._number;
    }

    public equals(square: Square): boolean {
        return this._letter == square._letter
            && this._number == square._number;
    }

    public toJSON() {
        return {
            square: this.toString()
        }
    }

    public toString() {
        return reverseLetterMap.get(this._letter)! + reverseNumberMap.get(this._number);
    }
}

export class Move {
    private _from: Square;
    private _to: Square;
    private _isBecameKing: boolean;

    constructor(from: Square, to: Square, isBecameKing: boolean = false) {
        this._from = from;
        this._to = to;
        this._isBecameKing = isBecameKing;
    }

    public getFrom(): Square {
        return this._from;
    }

    public getTo(): Square {
        return this._to;
    }

    public isBecameKing(): boolean {
        return this._isBecameKing;
    }

    public toJSON() {
        return {
            from: this._from.toString(),
            to: this._to.toString(),
            isBecameKing: this._isBecameKing,
        }
    }
}

export class Capture {
    private _move: Move;
    private _squaresToClear: Square[];
    private _isBecameKing: boolean;

    constructor(move: Move, squaresToClear: Square[], isBecameKing: boolean = false) {
        this._move = move;
        this._squaresToClear = squaresToClear;
        this._isBecameKing = isBecameKing;
    }

    public getMove(): Move {
        return this._move;
    }

    public getSquaresToClear(): Square[] {
        return this._squaresToClear;
    }

    public isBecameKing(): boolean {
        return this._isBecameKing;
    }

    public merge(capture: Capture): Capture {
        const isBecameKing = this._isBecameKing || capture._isBecameKing;
        return new Capture(new Move(this._move.getFrom(), capture._move.getTo(), isBecameKing),
            this._squaresToClear.concat(capture._squaresToClear), isBecameKing);
    }

    public toJSON() {
        return {
            move: this._move,
            squareToClear: this._squaresToClear.map(s => s.toString()),
            isBecameKing: this._isBecameKing,
        }
    }
}

export class Field {
    private _field: Value[][];

    constructor(field: Value[][]) {
        this._field = field;
    };

    public getField(): Value[][] {
        return this._field;
    }

    //Throw exception or just return bool?
    //Remember, that function works correctly with kings only if white start from line 1 and black from line 8
    public move(move: Move): void {
        let from = move.getFrom();
        let to = move.getTo();
        if (to.getNumber() == SquareNumber._8 && this._field[from.getLetter()][from.getNumber()] == white) {
            this._field[from.getLetter()][from.getNumber()] = whiteKing;
        } else if (to.getNumber() == SquareNumber._1 && this._field[from.getLetter()][from.getNumber()] == black) {
            this._field[from.getLetter()][from.getNumber()] = blackKing;
        }
        this._field[to.getLetter()][to.getNumber()] = this._field[from.getLetter()][from.getNumber()];
        this._field[from.getLetter()][from.getNumber()] = empty;
    }

    public capture(capture: Capture): void {
        this.move(capture.getMove());
        if (capture.isBecameKing()) {
            const targetSquare = capture.getMove().getTo();
            const value = this.getValue(targetSquare);
            if (value == white) {
                this.setValue(targetSquare, whiteKing);
            } else if (value == black) {
                this.setValue(targetSquare, blackKing);
            }
        }
        for (const squareToClear of capture.getSquaresToClear()) {
            this._field[squareToClear.getLetter()][squareToClear.getNumber()] = empty;
        }
    }

    public apply(choice: Move | Capture): void {
        if (choice instanceof Move) {
            this.move(choice);
        } else {
            this.capture(choice);
        }
    }

    public getValue(square: Square): Value {
        return this._field[square.getLetter()][square.getNumber()];
    }

    public setValue(square: Square, value: Value): void {
        this._field[square.getLetter()][square.getNumber()] = value;
    }

    //Does the same as getValue, but by index
    public get(letterIndex: number, numberIndex: number): Value {
        return this._field[letterIndex][numberIndex];
    }

    //Does the same as setValue, but by index
    public set(letterIndex: number, numberIndex: number, value: Value): void {
        this._field[letterIndex][numberIndex] = value;
    }

    public getSquareMoves(square: Square): Move[] {
        let i = square.getLetter();
        let j = square.getNumber();
        let moves = [];
        if (this._field[i][j] == white) {
            //⬉
            if (i - 1 >= 0 && j - 1 >= 0 && this._field[i - 1][j - 1] == empty) {
                moves.push(new Move(new Square(i, j), new Square(i - 1, j - 1), j - 1 == SquareNumber._8));
            }
            //⬋
            if (i + 1 < this._field.length && j - 1 >= 0 && this._field[i + 1][j - 1] == empty) {
                moves.push(new Move(new Square(i, j), new Square(i + 1, j - 1), j - 1 == SquareNumber._8));
            }
        } else if (this._field[i][j] == black) {
            //⬊
            if (i + 1 < this._field.length && j + 1 < this._field[i].length && this._field[i + 1][j + 1] == empty) {
                moves.push(new Move(new Square(i, j), new Square(i + 1, j + 1), j + 1 == SquareNumber._1));
            }
            //⬈
            if (i - 1 >= 0 && j + 1 < this._field[i].length && this._field[i - 1][j + 1] == empty) {
                moves.push(new Move(new Square(i, j), new Square(i - 1, j + 1), j + 1 == SquareNumber._1));
            }
        } else if (this._field[i][j] == whiteKing || this._field[i][j] == blackKing) {
            moves = moves.concat(this.kingMoves(i, j));
        }
        return moves;
    }

    public getOneMoveCaptures(square: Square): Capture[] {
        return this.getSquareOneMoveCaptures(this, square);
    }

    public getMoves(color: Color): Move[] {
        let moves = [];
        if (color == white) {
            for (let i = 0; i < this._field.length; i++) {
                for (let j = 0; j < this._field[i].length; j++) {
                    if (this._field[i][j] == white || this._field[i][j] == whiteKing) {
                        moves = moves.concat(this.getSquareMoves(new Square(i, j)));
                    }
                }
            }
        } else {
            for (let i = 0; i < this._field.length; i++) {
                for (let j = 0; j < this._field[i].length; j++) {
                    if (this._field[i][j] == black || this._field[i][j] == blackKing) {
                        moves = moves.concat(this.getSquareMoves(new Square(i, j)));
                    }
                }
            }
        }
        return moves;
    }

    public getCaptures(color: Color): Capture[] {
        let captures = [];
        if (color == white) {
            for (let i = 0; i < this._field.length; i++) {
                for (let j = 0; j < this._field[i].length; j++) {
                    if (this._field[i][j] == white || this._field[i][j] == whiteKing) {
                        captures = captures.concat(this.getSquareCaptures(new Field(structuredClone(this._field)), new Square(i, j)));
                    }
                }
            }
        } else {
            for (let i = 0; i < this._field.length; i++) {
                for (let j = 0; j < this._field[i].length; j++) {
                    if (this._field[i][j] == black || this._field[i][j] == blackKing) {
                        captures = captures.concat(this.getSquareCaptures(new Field(structuredClone(this._field)), new Square(i, j)));
                    }
                }
            }
        }
        return captures;
    }

    private getSquareCaptures(field: Field, square: Square): Capture[] {
        let captures = this.getSquareOneMoveCaptures(field, square);
        if (captures.length == 0) {
            return [];
        }

        let i = 0;
        while (i <  captures.length) {
            let fieldCopy = new Field(structuredClone(field._field));
            let capture = captures[i];
            fieldCopy.capture(capture);
            let subCaptures = this.getSquareCaptures(fieldCopy, capture.getMove().getTo());
            if (subCaptures.length != 0) {
                captures.splice(i, 1);
            } else {
                i++;
            }
            for (let subCapture of subCaptures) {
                captures.push(capture.merge(subCapture));
            }
        }

        return captures;
    }

    private getSquareOneMoveCaptures(field: Field, square: Square): Capture[] {
        let captures: Capture[] = [];
        const value = field._field[square.getLetter()][square.getNumber()];
        if (value == white) {
            //⬉
            let enemy = new Square(square.getLetter() - 1, square.getNumber() - 1);
            let jumpTo = new Square(square.getLetter() - 2, square.getNumber() - 2);
            if (enemy.getLetter() >= 0 && enemy.getNumber() >= 0 && jumpTo.getLetter() >= 0 && jumpTo.getNumber() >= 0) {
                if ((field.getValue(enemy) == black || field.getValue(enemy) == blackKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._8;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬋
            enemy = new Square(square.getLetter() + 1, square.getNumber() - 1);
            jumpTo = new Square(square.getLetter() + 2, square.getNumber() - 2);
            if (enemy.getLetter() < field._field.length && enemy.getNumber() >= 0
                && jumpTo.getLetter() < field._field.length && jumpTo.getNumber() >= 0) {
                if ((field.getValue(enemy) == black || field.getValue(enemy) == blackKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._8;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬊
            enemy = new Square(square.getLetter() + 1, square.getNumber() + 1);
            jumpTo = new Square(square.getLetter() + 2, square.getNumber() + 2);
            if (enemy.getLetter() < field._field.length && enemy.getNumber() < field._field.length
                && jumpTo.getLetter() < field._field.length && jumpTo.getNumber() < field._field.length) {
                if ((field.getValue(enemy) == black || field.getValue(enemy) == blackKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._8;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬈
            enemy = new Square(square.getLetter() - 1, square.getNumber() + 1);
            jumpTo = new Square(square.getLetter() - 2, square.getNumber() + 2);
            if (enemy.getLetter() >= 0 && enemy.getNumber() < field._field.length
                && jumpTo.getLetter() >= 0 && jumpTo.getNumber() < field._field.length) {
                if ((field.getValue(enemy) == black || field.getValue(enemy) == blackKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._8;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
        } else if (value == whiteKing) {
            //⬉
            let i = square.getLetter() - 1;
            let j = square.getNumber() - 1;
            let enemy = null;
            while (i >= 0 && j >= 0) {
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    break;
                }
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    enemy = new Square(i, j);
                    i--;
                    j--;
                    break;
                }
                i--;
                j--;
            }
            while (i >= 0 && j >= 0
                && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i--;
                j--;
            }


            //⬋
            i = square.getLetter() + 1;
            j = square.getNumber() - 1;
            enemy = null;
            while (i < field._field.length && j >= 0) {
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    break;
                }
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    enemy = new Square(i, j);
                    i++;
                    j--;
                    break;
                }
                i++;
                j--;
            }
            while (i < field._field.length && j >= 0
                && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i++;
                j--;
            }

            //⬊
            i = square.getLetter() + 1;
            j = square.getNumber() + 1;
            enemy = null;
            while (i < field._field.length && j < field._field.length) {
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    break;
                }
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    enemy = new Square(i, j);
                    i++;
                    j++;
                    break;
                }
                i++;
                j++;
            }
            while (i < field._field.length && j < field._field.length
                && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i++;
                j++;
            }

            //⬈
            i = square.getLetter() - 1;
            j = square.getNumber() + 1;
            enemy = null;
            while (i >= 0 && j < field._field.length) {
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    break;
                }
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    enemy = new Square(i, j);
                    i--;
                    j++;
                    break;
                }
                i--;
                j++;
            }
            while (i >= 0 && j < field._field.length
                && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i--;
                j++;
            }
        } else if (value == black) {
            //⬉
            let enemy = new Square(square.getLetter() - 1, square.getNumber() - 1);
            let jumpTo = new Square(square.getLetter() - 2, square.getNumber() - 2);
            if (enemy.getLetter() >= 0 && enemy.getNumber() >= 0 && jumpTo.getLetter() >= 0 && jumpTo.getNumber() >= 0) {
                if ((field.getValue(enemy) == white || field.getValue(enemy) == whiteKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._1;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬋
            enemy = new Square(square.getLetter() + 1, square.getNumber() - 1);
            jumpTo = new Square(square.getLetter() + 2, square.getNumber() - 2);
            if (enemy.getLetter() < field._field.length && enemy.getNumber() >= 0
                && jumpTo.getLetter() < field._field.length && jumpTo.getNumber() >= 0) {
                if ((field.getValue(enemy) == white || field.getValue(enemy) == whiteKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._1;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬊
            enemy = new Square(square.getLetter() + 1, square.getNumber() + 1);
            jumpTo = new Square(square.getLetter() + 2, square.getNumber() + 2);
            if (enemy.getLetter() < field._field.length && enemy.getNumber() < field._field.length
                && jumpTo.getLetter() < field._field.length && jumpTo.getNumber() < field._field.length) {
                if ((field.getValue(enemy) == white || field.getValue(enemy) == whiteKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._1;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
            //⬈
            enemy = new Square(square.getLetter() - 1, square.getNumber() + 1);
            jumpTo = new Square(square.getLetter() - 2, square.getNumber() + 2);
            if (enemy.getLetter() >= 0 && enemy.getNumber() < field._field.length
                && jumpTo.getLetter() >= 0 && jumpTo.getNumber() < field._field.length) {
                if ((field.getValue(enemy) == white || field.getValue(enemy) == whiteKing)
                    && field.getValue(jumpTo) == empty) {
                    const isBecameKing = jumpTo.getNumber() == SquareNumber._1;
                    captures.push(new Capture(new Move(square, jumpTo, isBecameKing), [enemy], isBecameKing));
                }
            }
        } else if (value == blackKing) {
            //⬉
            let i = square.getLetter() - 1;
            let j = square.getNumber() - 1;
            let enemy = null;
            while (i >= 0 && j >= 0) {
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    break;
                }
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    enemy = new Square(i, j);
                    i--;
                    j--;
                    break;
                }
                i--;
                j--;
            }
            while (i >= 0 && j >= 0
            && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i--;
                j--;
            }


            //⬋
            i = square.getLetter() + 1;
            j = square.getNumber() - 1;
            enemy = null;
            while (i < field._field.length && j >= 0) {
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    break;
                }
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    enemy = new Square(i, j);
                    i++;
                    j--;
                    break;
                }
                i++;
                j--;
            }
            while (i < field._field.length && j >= 0
            && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i++;
                j--;
            }

            //⬊
            i = square.getLetter() + 1;
            j = square.getNumber() + 1;
            enemy = null;
            while (i < field._field.length && j < field._field.length) {
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    break;
                }
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    enemy = new Square(i, j);
                    i++;
                    j++;
                    break;
                }
                i++;
                j++;
            }
            while (i < field._field.length && j < field._field.length
            && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i++;
                j++;
            }

            //⬈
            i = square.getLetter() - 1;
            j = square.getNumber() + 1;
            enemy = null;
            while (i >= 0 && j < field._field.length) {
                if (field._field[i][j] == black || field._field[i][j] == blackKing) {
                    break;
                }
                if (field._field[i][j] == white || field._field[i][j] == whiteKing) {
                    enemy = new Square(i, j);
                    i--;
                    j++;
                    break;
                }
                i--;
                j++;
            }
            while (i >= 0 && j < field._field.length
            && field._field[i][j] == empty) {
                captures.push(new Capture(new Move(square, new Square(i, j)), [enemy]));
                i--;
                j++;
            }
        }
        return captures;
    }

    private kingMoves(letterIndex: number, numberIndex: number): Move[] {
        let moves = [];

        //⬉ ⬋ ⬈ ⬊
        let moveI = letterIndex - 1;
        let moveJ = numberIndex - 1;
        while (moveI >= 0 && moveJ >= 0 && this._field[moveI][moveJ] == empty) {
            moves.push(new Move(new Square(letterIndex, numberIndex), new Square(moveI, moveJ)));
            moveJ--;
            moveI--;
        }

        moveI = letterIndex + 1;
        moveJ = numberIndex - 1;
        while (moveI < this._field.length && moveJ >= 0 && this._field[moveI][moveJ] == empty) {
            moves.push(new Move(new Square(letterIndex, numberIndex), new Square(moveI, moveJ)));
            moveJ--;
            moveI++;
        }

        moveI = letterIndex - 1;
        moveJ = numberIndex + 1;
        while (moveI >= 0 && moveJ < this._field[moveI].length && this._field[moveI][moveJ] == empty) {
            moves.push(new Move(new Square(letterIndex, numberIndex), new Square(moveI, moveJ)));
            moveJ++;
            moveI--;
        }

        moveI = letterIndex + 1;
        moveJ = numberIndex + 1;
        while (moveI < this._field.length && moveJ < this._field[moveI].length && this._field[moveI][moveJ] == empty) {
            moves.push(new Move(new Square(letterIndex, numberIndex), new Square(moveI, moveJ)));
            moveJ++;
            moveI++;
        }
        return moves;
    }
}

export interface Choice {
    choice: Move | Capture;
    evaluation: number;
}

export class AI {
    private _color: Color;

    constructor(color: Color) {
        this._color = color;
    }

    //Really can be changed
    private evaluate(field: Field): number {
        let score = 0;
        const selfCheckerValue = 1,
            enemyCheckerValue = 1,
            selfKingValue = 3,
            enemyKingValue = 7;

        function isOpponent(selfColor: Color, checkerValue: Value): boolean {
            return !(selfColor == white && (checkerValue == white || checkerValue == whiteKing)
                || selfColor == black && (checkerValue == black || checkerValue == blackKing));

        }

        for (let i = 0; i < 8; i++) {
            for (let j = 0; j < 8; j++) {
                const value = field.get(i, j);
                if (value != empty) {
                    if (isOpponent(this._color, value)) {
                        if (value == white || value == black) {
                            score -= enemyCheckerValue;
                        } else {
                            score -= enemyKingValue;
                        }
                    } else {
                        if (value == white || value == black) {
                            score += selfCheckerValue;
                        } else {
                            score += selfKingValue;
                        }
                    }
                }
            }
        }
        return score;
    }

    private minmax(field: Field, depth: number, alpha: number, beta: number, turn: Color): Choice {
        let captures = field.getCaptures(turn);
        let moves = field.getMoves(turn);
        if (depth <= 0 || (captures.length == 0 && moves.length == 0)) {
            return {choice: null, evaluation: this.evaluate(field)};
        }

        if (turn == this._color) {
            let bestChoice: Choice = {choice: null, evaluation: -Infinity};
            if (captures.length != 0) {
                for (const capture of captures) {
                    let fieldCopy = new Field(structuredClone(field.getField()));
                    fieldCopy.capture(capture);
                    let choice = this.minmax(fieldCopy, depth - 1, alpha, beta, turn == white ? black : white);
                    if (choice.evaluation > bestChoice.evaluation) {
                        bestChoice.choice = capture;
                        bestChoice.evaluation = choice.evaluation;
                    }
                    alpha = Math.max(alpha, choice.evaluation);
                    if (alpha >= beta) break;
                }
            } else {
                for (const move of moves) {
                    let fieldCopy = new Field(structuredClone(field.getField()));
                    fieldCopy.move(move);
                    let choice = this.minmax(fieldCopy, depth - 1, alpha, beta, turn == white ? black : white);
                    if (choice.evaluation > bestChoice.evaluation) {
                        bestChoice.choice = move;
                        bestChoice.evaluation = choice.evaluation;
                    }
                    alpha = Math.max(alpha, choice.evaluation);
                    if (alpha >= beta) break;
                }
            }
            return bestChoice;
        } else {
            let bestOpponentChoice: Choice = {choice: null, evaluation: +Infinity};
            if (captures.length != 0) {
                for (const capture of captures) {
                    let fieldCopy = new Field(structuredClone(field.getField()));
                    fieldCopy.capture(capture);
                    let choice = this.minmax(fieldCopy, depth - 1, alpha, beta, turn == white ? black : white);
                    if (choice.evaluation < bestOpponentChoice.evaluation) {
                        bestOpponentChoice.choice = capture;
                        bestOpponentChoice.evaluation = choice.evaluation;
                    }
                    beta = Math.min(beta, choice.evaluation);
                    if (alpha >= beta) break;
                }
            } else {
                for (const move of moves) {
                    let fieldCopy = new Field(structuredClone(field.getField()));
                    fieldCopy.move(move);
                    let choice = this.minmax(fieldCopy, depth - 1, alpha, beta, turn == white ? black : white);
                    if (choice.evaluation < bestOpponentChoice.evaluation) {
                        bestOpponentChoice.choice = move;
                        bestOpponentChoice.evaluation = choice.evaluation;
                    }
                    beta = Math.min(beta, choice.evaluation);
                    if (alpha >= beta) break;
                }
            }
            return bestOpponentChoice;
        }
    }

    public decide(field: Field, level: number): Move | Capture {
        let depth = level * 2;
        let choice = this.minmax(field, depth, -Infinity, +Infinity, this._color);
        return choice.choice;
    }
}