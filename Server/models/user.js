const mongoose = require("mongoose");
const Schema = mongoose.Schema;
const userSchema = new Schema({
    name: String,
    follows: [String],
    avatar: String
});

module.exports = mongoose.model("User", userSchema);
