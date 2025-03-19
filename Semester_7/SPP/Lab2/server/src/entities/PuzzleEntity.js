import {Sequelize, DataTypes} from 'sequelize';
import {Type} from "./TypeEntity.js";

const sequelize = new Sequelize({
    dialect: 'sqlite',
    storage: './db/puzzles.db'
});

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