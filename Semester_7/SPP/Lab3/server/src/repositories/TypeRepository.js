import {Type} from "../entities/TypeEntity.js";
import {SqlError} from "../exceptions/SqlError.js";

class TypeRepository {

    async getTypes() {
        try {
            return await Type.findAll();
        } catch (error) {
            throw new SqlError("Can't obtain types from db");
        }
    }

    async createType(type) {
        try {
            return await Type.create(type);
        } catch (error) {
            throw new SqlError("Can't persist type in db");
        }
    }
}

export const typeRepository = new TypeRepository();