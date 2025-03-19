import {Puzzle} from "./PuzzleEntity.js";
import {Type} from "./TypeEntity.js";
import {User} from "./UserEntity.js";
import {Token} from "./TokenEntity.js";

Puzzle.belongsTo(Type, {
    foreignKey: 'typeId',
    targetKey: 'id'
});

Type.hasMany(Puzzle, {
    foreignKey: 'typeId',
    sourceKey: 'id'
});

Token.belongsTo(User, {
    foreignKey: 'userId',
    targetKey: 'id'
});

User.hasOne(Token, {
    foreignKey: 'userId',
    sourceKey: 'id'
});