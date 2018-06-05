const graphql = require("graphql");
const { PubSub, withFilter } = require("graphql-subscriptions");

const pubSub = new PubSub();
const MESSAGE_WAS_ADDED_TOPIC = "newMessage";

const {
    GraphQLObjectType,
    GraphQLString,
    GraphQLSchema,
    GraphQLID,
    GraphQLList,
    GraphQLNonNull,
    GraphQLInt,
    GraphQLBoolean
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
        },
        followersCount: {
            type: new GraphQLNonNull(GraphQLInt),
            resolve(parent, args) {
                return User.count({ follows: parent.id });
            }
        },
        feed: {
            type: new GraphQLList(PostType),
            resolve(parent, args) {
                console.log(parent.follows);
                return Post.find({
                    authorId: { $in: parent.follows }
                }).sort("-date");
            }
        },
        follows: { type: new GraphQLList(GraphQLID) },
        followsCount: {
            type: new GraphQLNonNull(GraphQLInt),
            resolve(parent, args) {
                return parent.follows.length;
            }
        },
        followsUsers: {
            type: new GraphQLList(UserType),
            resolve(parent, args) {
                return User.find({
                    _id: { $in: parent.follows }
                });
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
            resolve(parent, args, context) {
                return User.findById(args.id || context._id);
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
                authorId: { type: GraphQLID }
            },
            async resolve(parent, args, context) {
                let post = new Post({
                    content: args.content,
                    authorId: args.authorId || context._id,
                    date: new Date()
                });
                post = await post.save();
                pubSub.publish(MESSAGE_WAS_ADDED_TOPIC, { messageAdded: post });
                return post;
            }
        },
        follow: {
            type: UserType,
            args: {
                follower: { type: new GraphQLNonNull(GraphQLID) },
                user: { type: new GraphQLNonNull(GraphQLID) }
            },
            resolve(parent, args) {
                return User.findByIdAndUpdate(
                    args.follower,
                    { $push: { follows: args.user } },
                    { new: true, upsert: true }
                );
            }
        }
    }
});

const Subscription = new GraphQLObjectType({
    name: "Subscription",
    fields: {
        messageAdded: {
            type: PostType,
            args: {
                userId: { type: new GraphQLNonNull(GraphQLID) }
            },
            subscribe: withFilter(
                () => pubSub.asyncIterator(MESSAGE_WAS_ADDED_TOPIC),
                (payload, variables) => {
                    return payload.userId === variables.authorId;
                }
            )
        }
    }
});

module.exports = new GraphQLSchema({
    query: RootQuery,
    mutation: Mutation,
    subscription: Subscription
});
