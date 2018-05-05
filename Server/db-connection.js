const mongoose = require("mongoose");
module.exports = function() {
    mongoose.connect(
        "mongodb://ruslan:test123@ds163119.mlab.com:63119/newsfeed"
    );
    mongoose.connection.once("open", () => {
        console.log("connected to database");
    });
};
