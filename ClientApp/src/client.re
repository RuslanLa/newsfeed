/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache() /* Create an HTTP Link */;

let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());

let wsLink = ApolloLinks.createWsLink(~uri="ws://localhost:4000/graphql", ());

let link = ApolloLinks.split(query => false, wsLink, httpLink);

let instance =
  ReasonApollo.createApolloClient(~link, ~cache=inMemoryCache, ());