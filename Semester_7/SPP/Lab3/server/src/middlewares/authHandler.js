import {ApiError} from "../exceptions/ApiError.js";
import {tokenService} from "../services/TokenService.js";

export default function authHandler(req, res, next) {
    try {
        const authHeader = req.headers.authorization;
        if (!authHeader) {
            return next(ApiError.Unauthorized('Invalid access token'));
        }
        const accessToken = authHeader.split(' ')[1];
        if (!accessToken) {
            return next(ApiError.Unauthorized('Invalid access token'));
        }
        const userData = tokenService.validateAccessToken(accessToken);
        if (!userData) {
            return next(ApiError.Unauthorized('Invalid access token'));
        }
        req.user = userData;
        next();
    } catch (e) {
        return next(ApiError.Unauthorized('Invalid access token'));
    }
}