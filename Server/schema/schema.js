const graphql = require("graphql");

const {
    GraphQLObjectType,
    GraphQLString,
    GraphQLSchema,
    GraphQLID,
    GraphQLList
} = graphql;
const _ = require("lodash");

const Post = require("../models/post");
const User = require("../models/user");

const PostType = new GraphQLObjectType({
    name: "Post",
    fields: () => ({
        id: {
            type: GraphQLID
        },
        content: { type: GraphQLString },
        date: { type: GraphQLString },
        author: {
            type: UserType,
            resolve(parent, args) {
                // return _.find(users, { id: parent.authorId });
            }
        }
    })
});

const UserType = new GraphQLObjectType({
    name: "User",
    fields: () => ({
        id: {
            type: GraphQLID
        },
        name: { type: GraphQLString },
        avatar: { type: GraphQLString },
        posts: {
            type: new GraphQLList(PostType),
            resolve(parent, args) {
                // return _.filter(posts, { authorId: parent.id });
            }
        }
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
                // return _.find(posts, { id: args.id });
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
                // return _.find(users, { id: args.id });
            }
        },
        posts: {
            type: new GraphQLList(PostType),
            resolve(parent, args) {
                // return posts;
            }
        },
        users: {
            type: new GraphQLList(UserType),
            resolve(parent, args) {
                // return users;
            }
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery
});
