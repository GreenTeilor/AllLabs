import jwt from "jsonwebtoken";
import {tokenRepository} from "../repositories/TokenRepository.js";

class TokenService {

    generateTokens(payload) {
        const accessToken = jwt.sign(payload, process.env.JWT_ACCESS_SECRET, {
            expiresIn: '30m'
        });
        const refreshToken = jwt.sign(payload, process.env.JWT_REFRESH_SECRET, {
            expiresIn: '30d'
        })
        return {
            accessToken,
            refreshToken
        }
    }

    validateAccessToken(accessToken) {
        try {
            return jwt.verify(accessToken, process.env.JWT_ACCESS_SECRET);
        } catch (e) {
            return null;
        }
    }

    validateRefreshToken(accessToken) {
        try {
            return jwt.verify(accessToken, process.env.JWT_REFRESH_SECRET);
        } catch (e) {
            return null;
        }
    }

    async createRefreshToken(userId, refreshToken) {
        return await tokenRepository.createRefreshToken(userId, refreshToken);
    }

    async removeRefreshToken(refreshToken) {
        return await tokenRepository.deleteRefreshToken(refreshToken);
    }

    async findRefreshToken(refreshToken) {
        return await tokenRepository.findRefreshToken(refreshToken);
    }
}

export const tokenService = new TokenService();