import {puzzleRepository} from "../repositories/PuzzleRepository.js";

class PuzzleService {

    async getPuzzles(filter) {
        return await puzzleRepository.getPuzzles(filter);
    }

    async createPuzzle(puzzle) {
        return await puzzleRepository.createPuzzle(puzzle);
    }

    async updatePuzzleType(puzzleId, typeId) {
        return await puzzleRepository.updatePuzzleType(puzzleId, typeId);
    }
}

export const puzzleService = new PuzzleService();