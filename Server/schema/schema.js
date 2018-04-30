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
const users = [
    {
        name: "Vladimir Putin",
        id: "1",
        follows: [],
        followers: [],
        avatar: "putin"
    },
    {
        name: "Ruslan Latypov",
        id: "2",
        follows: [],
        followers: [],
        avatar: "ruslan"
    },
    {
        name: "Some person",
        id: "3",
        follows: [],
        followers: [],
        avatar: "person"
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

const UserType = new GraphQLObjectType({
    name: "User",
    fields: () => ({
        id: {
            type: GraphQLID
        },
        name: { type: GraphQLString },
        avatar: { type: GraphQLString }
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
        },
        user: {
            type: UserType,
            args: {
                id: {
                    type: GraphQLID
                }
            },
            resolve(parent, args) {
                return _.find(users, { id: args.id });
            }
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery
});
