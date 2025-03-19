import {User} from "../entities/UserEntity.js"
import {SqlError} from "../exceptions/SqlError.js";

class UserRepository {

    async findByEmail(email) {
        let whereClause = { email }
        try {
            return await User.findOne({
                where: whereClause
            });
        } catch (error) {
            throw new SqlError("Can't obtain user from db");
        }
    }

    async findById(id) {
        let whereClause = { id }
        try {
            return await User.findOne({
                where: whereClause
            });
        } catch (error) {
            throw new SqlError("Can't obtain user from db");
        }
    }

    async findByActivationLink(activationLink) {
        let whereClause = { activationLink }
        try {
            return await User.findOne({
                where: whereClause
            });
        } catch (error) {
            throw new SqlError("Can't obtain user from db");
        }
    }

    async create(user) {
        try {
            return await User.create(user);
        } catch (error) {
            throw new SqlError("Can't persist user in db");
        }
    }
}

export const userRepository = new UserRepository();