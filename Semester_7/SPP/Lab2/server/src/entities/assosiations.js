import {Puzzle} from "./PuzzleEntity.js";
import {Type} from "./TypeEntity.js";

Puzzle.belongsTo(Type, {
    foreignKey: 'typeId',
    targetKey: 'id'
});

Type.hasMany(Puzzle, {
    foreignKey: 'typeId',
    sourceKey: 'id'
});