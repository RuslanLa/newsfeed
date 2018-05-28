const express = require("express");
const app = express();
const cors = require("cors");
const {createServer} = require("http");
const { graphqlExpress, graphiqlExpress } = require("apollo-server-express");
const chalk = require("chalk");
const graphqlHTPP = require("express-graphql");
const schema = require("./schema/schema");
const mongoose = require("mongoose");

const { SubscriptionServer } = require("subscriptions-transport-ws");

const { execute, subscribe } = require("graphql");
const bodyParser = require("body-parser");
const PORT = 4000;
mongoose.connect("mongodb://ruslan:test123@ds163119.mlab.com:63119/newsfeed");
mongoose.connection.once("open", () => {
    console.log("connected to database");
});
app.use('*' ,cors(`http:/localhost:${PORT}`));
app.use(
    "/graphql",
    bodyParser.json(),
    graphqlExpress({
        schema
    })
);

app.use(
    "/graphiql",
    graphiqlExpress({
        endpointURL: "/graphql",
        subscriptionsEndpoint: `ws://localhost:${PORT}/graphql`
    })
);

const ws = createServer(app);

ws.listen(PORT, () => {
    console.log(`Apollo Server is now running on http://localhost:${PORT}`);
    // Set up the WebSocket for handling GraphQL subscriptions
    new SubscriptionServer({
      execute,
      subscribe,
      schema
    }, {
      server: ws,
      path: '/graphql',
    })
});
