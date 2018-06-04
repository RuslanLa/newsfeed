const express = require("express");
const app = express();
const cors = require("cors");
const { createServer } = require("http");
const { graphqlExpress, graphiqlExpress } = require("apollo-server-express");
const schema = require("./schema/schema");
const mongoose = require("mongoose");

const { SubscriptionServer } = require("subscriptions-transport-ws");

const { execute, subscribe } = require("graphql");
const bodyParser = require("body-parser");
const { passport } = require("./passport-config");
const { authorizeUser } = require("./auth");
const connect = require("./db-connection");

// parse application/x-www-form-urlencoded
// for easier testing with Postman or plain HTML forms
app.use(bodyParser.urlencoded({
    extended: true
}));
const PORT = 4000;
connect();
app.use(passport.initialize());
app.use('*', cors(`http:/localhost:${PORT}`));
app.post("/login", bodyParser.json(), async function (req, res) {
    const name = ((req || {}).body || {}).name;
    const password = ((req || {}).body || {}).password;
    const { token, id } = (await authorizeUser(name, password)) || {};
    if (!token) {
        res.status(401).json({ message: "passwords did not match" });
        return;
    }
    res.json({ message: "ok", token: token, id: id });
});
app.use(
    "/graphql",
    bodyParser.json(),
    passport.authenticate('jwt', { session: false }), graphqlExpress({
        schema
    }));

app.use(
    "/graphiql",
    graphiqlExpress({
        endpointURL: "/graphql?auth_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjViMTE2NTgwMDQ5NGUyMzdmMDJmMjg5MSIsImlhdCI6MTUyNzg2Njk0Mn0.z664_eRec_TLk23XQYa3lTvxibNx4zsXmE79cLrkacQ&",
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
