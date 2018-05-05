const graphql = require("graphql");

const {
    GraphQLObjectType,
    GraphQLString,
    GraphQLSchema,
    GraphQLID,
    GraphQLList,
    GraphQLNonNull
} = graphql;
const _ = require("lodash");

const Post = require("../models/post");
const User = require("../models/user");

const PostType = new GraphQLObjectType({
    name: "Post",
    fields: () => ({
        id: {
            type: new GraphQLNonNull(GraphQLID)
        },
        content: { type: new GraphQLNonNull(GraphQLString) },
        date: { type: new GraphQLNonNull(GraphQLString) },
        author: {
            type: new GraphQLNonNull(UserType),
            resolve(parent, args) {
                return User.findById(parent.authorId);
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
        name: { type: new GraphQLNonNull(GraphQLString) },
        avatar: { type: new GraphQLNonNull(GraphQLString) },
        posts: {
            type: new GraphQLList(PostType),
            resolve(parent, args) {
                return Post.find({ authorId: parent.id }).sort("-date");
            }
        }
    })
});

const RootQuery = new GraphQLObjectType({
    name: "RootQueryType",
    fields: {
        post: {
            type: new GraphQLNonNull(PostType),
            args: {
                id: { type: GraphQLID }
            },
            resolve(parent, args) {
                return Post.findById(args.id);
            }
        },
        user: {
            type: new GraphQLNonNull(UserType),
            args: {
                id: {
                    type: GraphQLID
                }
            },
            resolve(parent, args) {
                return User.findById(args.id);
            }
        },
        posts: {
            type: new GraphQLList(PostType),
            resolve(parent, args) {
                return Post.find();
            }
        },
        users: {
            type: new GraphQLList(UserType),
            resolve(parent, args) {
                return User.find();
            }
        }
    }
});

const Mutation = new GraphQLObjectType({
    name: "Mutation",
    fields: {
        addUser: {
            type: UserType,
            args: {
                name: { type: new GraphQLNonNull(GraphQLString) },
                avatar: { type: GraphQLString }
            },
            resolve(parent, args) {
                let user = new User({
                    name: args.name,
                    avatar: args.avatar
                });

                return user.save();
            }
        },
        addPost: {
            type: PostType,
            args: {
                content: { type: new GraphQLNonNull(GraphQLString) },
                authorId: { type: new GraphQLNonNull(GraphQLID) }
            },
            resolve(parent, args) {
                let post = new Post({
                    content: args.content,
                    authorId: args.authorId,
                    date: new Date()
                });
                return post.save();
            }
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery,
    mutation: Mutation
});
