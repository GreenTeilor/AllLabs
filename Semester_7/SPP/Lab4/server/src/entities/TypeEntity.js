import {DataTypes} from 'sequelize';
import {sequelize} from "../repositories/sequelize.js";

export const Type = sequelize.define('Type', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        name: {
            type: DataTypes.STRING,
            allowNull: false
        }
    }, {
        tableName: 'types',
        timestamps: false,
    }
);