export class SqlError extends Error {

    constructor(message) {
        super(message);
        this.name = "SqlError";
    }
}