import graphql, {GraphQLSchema} from 'graphql';
import {puzzleService} from "../services/PuzzleService.js";
import {typeService} from "../services/TypeService.js";

const {GraphQLObjectType, GraphQLString,
    GraphQLID, GraphQLList} = graphql;

const TypeType = new GraphQLObjectType({
    name: 'type',
    fields: () => ({
        id: { type: GraphQLID },
        name: { type: GraphQLString },
        puzzles: {
            type: new GraphQLList(PuzzleType),
            async resolve(parent, args) {
                return await puzzleService.getPuzzles(parent.id);
            }
        }
    })
})

const PuzzleType = new GraphQLObjectType({
    name: 'puzzle',
    fields: () => ({
        id: { type: GraphQLID },
        name: { type: GraphQLString },
        type: {
            type: TypeType,
            async resolve(parent, args) {
                return {
                    id: parent.typeId,
                    name: parent.Type.name
                }
            }
        },
        date: { type: GraphQLString },
        file: { type: GraphQLString }
    })
})

const Query = new GraphQLObjectType({
    name: 'Query',
    fields: {
        puzzles: {
            type: new GraphQLList(PuzzleType),
            async resolve(parent, args) {
                return await puzzleService.getPuzzles('all');
            }
        },
        types: {
            type: new GraphQLList(TypeType),
            async resolve(parent, args) {
                return await typeService.getTypes();
            }
        }
    }
})

const Mutation = new GraphQLObjectType({
    name: 'Mutation',
    fields: {
        deletePuzzle: {
            type: PuzzleType,
            args: { id: { type: GraphQLID } },
            async resolve(parent, args, context) {
                return await puzzleService.deletePuzzle(args.id);
            }
        },
        deleteType: {
            type: TypeType,
            args: { id: { type: GraphQLID } },
            async resolve(parent, args, context) {
                return await typeService.deleteType(args.id);
            }
        }
    }
})

export default new GraphQLSchema({
    query: Query,
    mutation: Mutation
});