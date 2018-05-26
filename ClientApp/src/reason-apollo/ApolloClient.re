open ReasonApolloTypes;

type queryObj = {
  .
  "query": ReasonApolloTypes.queryString,
  "variables": Js.Json.t,
};

type mutationObj = {
  .
  "mutation": ReasonApolloTypes.queryString,
  "variables": Js.Json.t,
};

type generatedApolloClient = {
  .
  "query": [@bs.meth] (queryObj => string),
  "mutate": [@bs.meth] (mutationObj => string),
};

type fetch;

type linkOptions = {
  .
  "uri": string,
  "includeExtensions": Js.Nullable.t(bool),
  "fetch": Js.Nullable.t(fetch),
  "headers": Js.Nullable.t(Js.Json.t),
  "credentials": Js.Nullable.t(string),
  "fetchOptions": Js.Nullable.t(Js.Json.t)
};

type connectionCallback;

type wsLinkOptions = {
  .
  "timeout": Js.Nullable.t(int),
  "reconnect": Js.Nullable.t(bool),
  "reconnectionAttempts": Js.Nullable.t(int),
  "connectionCallback": Js.Nullable.t(connectionCallback),
  "lazy": Js.Nullable.t(bool),
  "inactivityTimeout": Js.Nullable.t(int)
};

type webSocketImplementation;

type wsLinkConfig = {
  .
  "uri": string,
  "options": Js.Nullable.t(wsLinkOptions),
  "webSocketImpl": Js.Nullable.t(webSocketImplementation)
};

[@bs.module "apollo-client"] [@bs.new]
external createApolloClientJS : 'a => generatedApolloClient = "ApolloClient";

[@bs.obj]
external apolloClientObjectParam :
  (
    ~link: apolloLink,
    ~cache: apolloCache,
    ~ssrMode: bool=?,
    ~ssrForceFetchDelay: int=?,
    ~connectToDevTools: bool=?,
    ~queryDeduplication: bool=?
  ) =>
  _ =
  "";