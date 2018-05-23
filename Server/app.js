const express = require("express");
const app = express();
const cors = require("cors");

const chalk = require("chalk");
const graphqlHTPP = require("express-graphql");
const schema = require("./schema/schema");
const mongoose = require("mongoose");

const { SubscriptionServer } = require("subscriptions-transport-ws");

const { execute, subscribe } = require("graphql");

mongoose.connect("mongodb://ruslan:test123@ds163119.mlab.com:63119/newsfeed");
mongoose.connection.once("open", () => {
    console.log("connected to database");
});
app.use(cors());
app.use(
    "/graphql",
    graphqlHTPP({
        schema,
        graphiql: true
    })
);

const server = app.listen(4000, () => {
    console.log(chalk.green("now listening for requests on port: 4000"));
});

SubscriptionServer.create(
    { schema, execute, subscribe },
    { server, path: "/graphql" }
);
