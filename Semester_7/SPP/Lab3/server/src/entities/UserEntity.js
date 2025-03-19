import {DataTypes} from 'sequelize';
import {sequelize} from "../repositories/sequelize.js";

export const User = sequelize.define('User', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        email: {
            type: DataTypes.STRING,
            unique: true,
            allowNull: false
        },
        password: {
            type: DataTypes.STRING,
            allowNull: false
        },
        isActivated : {
            type: DataTypes.BOOLEAN,
            defaultValue: false,
            allowNull: false
        },
        activationLink: {
            type: DataTypes.STRING
        }
    }, {
        tableName: 'users',
        timestamps: false,
    }
);