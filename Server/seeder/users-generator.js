const casual = require("casual");
const faker = require("faker");
const connect = require("../db-connection");
const User = require("../models/user");
const Post = require("../models/post");
var ObjectId = require("mongoose").Types.ObjectId;

Array.prototype.flatMap = function(lambda) {
    return Array.prototype.concat.apply([], this.map(lambda));
};
casual.define("user", function() {
    return {
        name: casual.username,
        avatar: faker.image.avatar()
    };
});

casual.define("users", function(count) {
    return Array.from({ length: count }, (x, i) => casual.user);
});

casual.define("post", function(authorId) {
    return {
        authorId,
        date: faker.date.past(),
        content: casual.sentences(
            Math.floor(faker.random.number({ min: 1, max: 3 }))
        )
    };
});
casual.define("posts", function(authorId, minCount, maxCount) {
    return Array.from(
        {
            length: Math.floor(
                faker.random.number({ min: minCount, max: maxCount })
            )
        },
        (v, i) => casual.post(authorId)
    );
});

connect();

const getUsersIds = () => {
    return User.find({})
        .select("_id")
        .exec();
};
const prinUserIds = async () => {
    const ids = await getUsersIds();
    console.log(ids);
};

const insertUsers = count => {
    const users = casual.users(count);
    return User.insertMany(users);
};
const randomFollows = (curId, ids, maxCount) => {
    const follows = [];
    const others = ids.filter(id => id != curId);
    const count = Math.floor(faker.random.number({ max: maxCount, min: 1 }));
    for (var i = 0; i < count; i++) {
        const newFollow = faker.random.arrayElement(ids);
        if (follows.includes(newFollow)) {
            continue;
        }
        follows.push(faker.random.arrayElement(ids));
    }
    return follows;
};
const insertUsersAndFillFollows = async count => {
    const users = await insertUsers(count);
    console.log("users are inserted");
    const ids = (await getUsersIds()).map(x => x._id);
    const usersWithFollows = ids.map(id => ({
        id,
        follows: randomFollows(id, ids, 100)
    }));
    console.log("follows are mapped");
    usersWithFollows.forEach(async user => {
        await User.findByIdAndUpdate(
            new ObjectId(user.id),
            {
                follows: user.follows
            },
            { upsert: false }
        ).exec();
    });
    console.log("follows are inserted");
    return ids;
};
const insertPosts = async (ids, maxCount) => {
    const posts = ids.flatMap(id => casual.posts(id, 4, maxCount));
    await Post.insertMany(posts);
    console.log("posts are inserted");
};
prinUserIds();
insertUsersAndFillFollows(400).then(async ids => {
    await insertPosts(ids, 50);
    process.exit(1);
});
