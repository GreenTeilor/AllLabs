import {userRepository} from "../repositories/UserRepository.js";
import {mailService} from "./MailService.js";
import {tokenService} from "./TokenService.js";
import {UserDto} from "../dto/UserDto.js";
import '../entities/assosiations.js';
import {ApiError} from "../exceptions/ApiError.js";
import bcrypt from "bcrypt";
import {v4} from "uuid";
import {User} from "../entities/UserEntity.js";

class UserService {

    async register(email, password) {
        const candidate = await userRepository.findByEmail(email);
        if (candidate) {
            throw ApiError.BadRequest(`User with email ${email} already exists`);
        }
        const hashPassword = await bcrypt.hash(password, 3);
        const activationLink = v4(); //uuid.v4()

        const user = await userRepository.create({
            email,
            password: hashPassword,
            activationLink
        });
        await mailService.sendActivationLink(email, `${process.env.API_URL}/api/v1/users/activate/${activationLink}`);

        const userDto = new UserDto(user);
        const tokens = tokenService.generateTokens({...userDto});
        await tokenService.createRefreshToken(userDto.id, tokens.refreshToken);

        return {
            ...tokens,
            user: userDto
        }
    }

    async activate(activationLink) {
        const user = await userRepository.findByActivationLink(activationLink);
        if (!user) {
            throw new Error('Incorrect activation link');
        }
        user.isActivated = true;
        let whereClause = {activationLink}
        await User.update(
            {isActivated: true},
            {where: whereClause}
        )
    }

    async login(email, password) {
        const user = await userRepository.findByEmail(email);
        if (!user) {
            throw ApiError.BadRequest(`No user with email ${email} found`);
        }
        const isPasswordCorrect = await bcrypt.compare(password, user.password);
        if (!isPasswordCorrect) {
            throw ApiError.BadRequest(`Invalid password`);
        }
        const userDto = new UserDto(user);
        const tokens = tokenService.generateTokens({...userDto});
        await tokenService.createRefreshToken(userDto.id, tokens.refreshToken);
        return {
            ...tokens,
            user: userDto
        }
    }

    async logout(refreshToken) {
        return await tokenService.removeRefreshToken(refreshToken);
    }

    async refresh(refreshToken) {
        if (!refreshToken) {
            throw ApiError.Unauthorized('Invalid refresh token');
        }
        const userData = tokenService.validateRefreshToken(refreshToken);
        const tokenFromDb = await tokenService.findRefreshToken(refreshToken);
        if (!userData || !tokenFromDb) {
            throw ApiError.Unauthorized('Invalid refresh token');
        }

        const user = await userRepository.findById(userData.id);
        const userDto = new UserDto(user);
        const tokens = tokenService.generateTokens({...userDto});
        await tokenService.createRefreshToken(userDto.id, tokens.refreshToken);
        return {
            ...tokens,
            user: userDto
        }
    }
}

export const userService = new UserService();