const mongoose = require("mongoose");
const { connectionString } = require("./private-config");
module.exports = function () {
    mongoose.connect(
        connectionString
    );
    mongoose.connection.once("open", () => {
        console.log("connected to database");
    });
};
