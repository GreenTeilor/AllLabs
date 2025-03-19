import {DataTypes} from 'sequelize';
import {sequelize} from "../repositories/sequelize.js";
import {Type} from "./TypeEntity.js";

export const Puzzle = sequelize.define('Puzzle', {
        id: {
            type: DataTypes.INTEGER,
            primaryKey: true,
            autoIncrement: true
        },
        name: {
            type: DataTypes.STRING,
            allowNull: false
        },
        typeId: {
            type: DataTypes.INTEGER,
            allowNull: false,
            references: {
                model: Type,
                key: 'id'
            }
        },
        date: {
            type: DataTypes.STRING,
            allowNull: false
        },
        file: {
            type: DataTypes.STRING,
            allowNull: false
        }
    },
    {
        tableName: 'puzzles',
        timestamps: false,
    }
);