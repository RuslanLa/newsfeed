const express = require("express");
const app = express();
const chalk = require("chalk");
const graphqlHTPP = require("express-graphql");
const schema = require("./schema/schema");
const mongoose = require("mongoose");

mongoose.connect("mongodb://ruslan:test123@ds163119.mlab.com:63119/newsfeed");
mongoose.connection.once("open", () => {
    console.log("connected to database");
});
app.use(
    "/graphql",
    graphqlHTPP({
        schema,
        graphiql: true
    })
);
app.listen(4000, () => {
    console.log(chalk.green("now listening for requests on port: 4000"));
});
