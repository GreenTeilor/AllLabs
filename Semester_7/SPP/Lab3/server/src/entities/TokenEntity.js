import {DataTypes} from 'sequelize';
import {sequelize} from "../repositories/sequelize.js";
import {User} from "./UserEntity.js";

export const Token = sequelize.define('Token', {
        userId: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            references: {
                model: User,
                key: 'id'
            }
        },
        refreshToken: {
            type: DataTypes.STRING,
            allowNull: false
        }
    }, {
        tableName: 'tokens',
        timestamps: false,
    }
);