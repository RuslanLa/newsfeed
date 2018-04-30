const express = require("express");
const app = express();
const chalk = require("chalk");
const graphqlHTPP = require("express-graphql");
const schema = require("./schema/schema");

app.use(
    "/graphql",
    graphqlHTPP({
        schema
    })
);
app.listen(4000, () => {
    console.log(chalk.green("now listening for requests on port: 4000"));
});
