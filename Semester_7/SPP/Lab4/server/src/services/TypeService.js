import {typeRepository} from "../repositories/TypeRepository.js";

class TypeService {

    async getTypes() {
        return await typeRepository.getTypes();
    }

    async createType(type){
        return await typeRepository.createType(type);
    }
}

export const typeService = new TypeService();