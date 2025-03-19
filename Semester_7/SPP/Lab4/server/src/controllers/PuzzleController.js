import {puzzleService} from "../services/PuzzleService.js";
import interceptor from "./ValidationInterceptor.js";

class PuzzleController {

    async getPuzzles(req, res, next) {
        try {
            const puzzles = await puzzleService.getPuzzles(req.query.filter);
            res.json(puzzles);
        } catch (e) {
            next(e);
        }
    }

    async createPuzzle(req, res, next) {
        try {
            const {name, date, type} = req.body;
            const file = req.file ? req.file.filename : null;
            let puzzle = {name, date, typeId: type, file};
            puzzle = await puzzleService.createPuzzle(puzzle);
            res.status(201);
            res.json(puzzle);
        } catch (e) {
            next(e);
        }
    }

    async updatePuzzleType(req, res, next) {
        try {
            const id = req.params.id;
            const type = req.body.type;
            const puzzle = await puzzleService.updatePuzzleType(id, type);
            res.json(puzzle);
        } catch (e) {
            next(e);
        }
    }
}

export const puzzleController = new PuzzleController();
interceptor.call(puzzleController, PuzzleController.prototype);