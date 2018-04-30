const graphql = require("graphql");

const { GraphQLObjectType, GraphQLString, GraphQLSchema, GraphQLID } = graphql;
const _ = require("lodash");

const posts = [
    {
        id: "1",
        content: "Hello world! How are you doing",
        date: new Date().toDateString()
    },
    {
        id: "2",
        content: "Ho ho ho",
        date: new Date().toDateString()
    },
    {
        id: "3",
        content: "Just some info",
        date: new Date().toDateString()
    }
];

const PostType = new GraphQLObjectType({
    name: "Post",
    fields: () => ({
        id: {
            type: GraphQLID
        },
        content: { type: GraphQLString },
        date: { type: GraphQLString }
    })
});

const RootQuery = new GraphQLObjectType({
    name: "RootQueryType",
    fields: {
        post: {
            type: PostType,
            args: {
                id: { type: GraphQLID }
            },
            resolve(parent, args) {
                return _.find(posts, { id: args.id });
            }
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery
});
