const mongoose = require("mongoose");
const Schema = mongoose.Schema;

const postSchema = new Schema({
    date: Date,
    content: String,
    authorId: String
});

module.exports = mongoose.model("Post", postSchema);
