import {Sequelize, DataTypes} from 'sequelize';

const sequelize = new Sequelize({
    dialect: 'sqlite',
    storage: './db/puzzles.db'
});

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