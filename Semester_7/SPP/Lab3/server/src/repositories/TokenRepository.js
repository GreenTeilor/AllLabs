import {Token} from '../entities/TokenEntity.js'
import {SqlError} from "../exceptions/SqlError.js";
import '../entities/assosiations.js';

class TokenRepository {

    async createRefreshToken(userId, refreshToken) {
        let whereClause = { userId }
        try {
            const tokenData = await Token.findOne({
                where: whereClause
            });
            if (tokenData) {
                tokenData.refreshToken = refreshToken;
                await Token.update(
                    { refreshToken },
                    { where: whereClause }
                )
                return tokenData;
            }
            return await Token.create({
                userId,
                refreshToken
            });
        } catch (error) {
            throw new SqlError("Can't obtain/persist db refresh token");
        }
    }

    async deleteRefreshToken(refreshToken) {
        let whereClause = { refreshToken }
        try {
            const token = await Token.findOne({
                where: whereClause
            });
            await Token.destroy({
                where: whereClause
            });
            return token;
        } catch (error) {
            throw new SqlError("Can't delete refresh token from db");
        }
    }

    async findRefreshToken(refreshToken) {
        try {
            let whereClause = {refreshToken}
            return await Token.findOne({
                where: whereClause
            });
        } catch (error) {
            throw new SqlError("Can't execute refresh token find operation in db");
        }
    }
}

export const tokenRepository  = new TokenRepository();

