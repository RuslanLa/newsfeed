const mongoose = require("mongoose");
const Schema = mongoose.Schema;
var userRef = new Schema({ name: String });

const userSchema = new Schema({
    name: String,
    follows: [userRef],
    followers: [userRef],
    avatar: String
});

module.exports = mongoose.model("User", userSchema);
