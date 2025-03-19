import {typeRepository} from "../repositories/TypeRepository.js";
import {puzzleRepository} from "../repositories/PuzzleRepository.js";

class TypeService {

    async getTypes() {
        return await typeRepository.getTypes();
    }

    async createType(type){
        return await typeRepository.createType(type);
    }

    async deleteType(typeId){
        await puzzleRepository.deleteAllByTypeId(typeId);
        return await typeRepository.deleteType(typeId);
    }
}

export const typeService = new TypeService();