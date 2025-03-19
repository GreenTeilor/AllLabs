import {Puzzle} from '../entities/PuzzleEntity.js'
import {Type} from "../entities/TypeEntity.js";
import '../entities/assosiations.js';
import {SqlError} from "../exceptions/SqlError.js";

class PuzzleRepository {

    async getPuzzles(filter) {
        filter = filter || 'all';
        let whereClause = filter !== 'all' ? {typeId: filter} : {};

        try {
            return await Puzzle.findAll({
                where: whereClause,
                include: {
                    model: Type,
                    attributes: ['id', 'name']
                }
            });
        } catch (error) {
            throw new SqlError("Can't obtain puzzles from db");
        }
    }

    async createPuzzle(puzzle) {
        try {
            return await Puzzle.create(puzzle);
        } catch (error) {
            throw new SqlError("Can't persist puzzle in db");
        }
    }

    async updatePuzzleType(puzzleId, typeId) {
        let whereClause = {id: puzzleId}

        try {
            await Puzzle.update(
                {typeId: typeId},
                {where: whereClause}
            )
            return await Puzzle.findOne({
                where: whereClause,
                include: {
                    model: Type,
                    attributes: ['id', 'name']
                }
            });
        } catch (error) {
            throw new SqlError("Can't update puzzle in db");
        }
    }
}

export const puzzleRepository = new PuzzleRepository();