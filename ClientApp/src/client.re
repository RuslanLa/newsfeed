/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache() /* Create an HTTP Link */;

let httpLink =
  ApolloLinks.createHttpLink(~uri=Url.Consts.graphqlHttp, ());

let wsLink = ApolloLinks.createWsLink(~uri=Url.Consts.graphqlWs, ());
let contextHandler = () =>
  switch (Dom.Storage.(localStorage |> getItem("token"))) {
    | None =>{
      Js.log("NOT AUTHORIZED!!!!!!");
      {"headers":{"authorization":""}};
    }
    | Some(data) =>{
      /* prevContext##headers##authorization = "Bearer" ++ data; */
      {"headers": {"authorization": "Bearer " ++ data}};
    }
};
let contextLink =
  ApolloLinks.createContextLink(contextHandler);

let link =
  ApolloLinks.split(
    operation => {
      let definition = ReasonApolloUtils.getMainDefinition(operation##query);
      Js.log(definition);
      Js.log(definition##operation === "subscription");
      definition##operation === "subscription";
    },
    wsLink,
    httpLink
  );

let authorizedLink = ApolloLinks.concat(contextLink, link);

let instance =
  ReasonApollo.createApolloClient(
    ~link=authorizedLink,
    ~cache=inMemoryCache,
    ()
  );