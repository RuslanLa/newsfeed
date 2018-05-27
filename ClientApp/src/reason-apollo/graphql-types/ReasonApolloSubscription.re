open ReasonApolloTypes;

module SubscriptionFactory = (Config: Config) => {
  [@bs.module] external gql : ReasonApolloTypes.gql = "graphql-tag";
  [@bs.module "react-apollo"]
  external subscriptionComponent : ReasonReact.reactClass = "Subscription";
  let graphqlSubscriptionAST = gql(. Config.query);
  type response =
    | Loading
    | Error(apolloError)
    | Data(Config.t)
    | NotCalled;
  type renderPropObj = {
    data: option(Config.t),
    loading: bool,
    result: response,
    error: option(apolloError),
  };
  type renderPropObjJS = {
    .
    "loading": bool,
    "data": Js.Nullable.t(Js.Json.t),
    "error": Js.Nullable.t(apolloError)
  };
  type apolloSubscription =
    (~variables: Js.Json.t=?, ~shouldResubscribe: bool=?, unit) =>
    Js.Promise.t(renderPropObjJS);
  [@bs.obj]
  external makeSubscribeParams :
    (~variables: Js.Json.t=?, ~shouldResubscribe: bool=?) => _ =
    "";
  let apolloSubscriptionFactory =
      (~jsSubscription, ~variables=?, ~shouldResubscribe=?, ()) =>
      jsSubscription(makeSubscribeParams(~variables?, ~shouldResubscribe?));
  let apolloDataToReason: renderPropObjJS => response =
    apolloData =>
      switch (
        apolloData##loading,
        apolloData##data |> ReasonApolloUtils.getNonEmptyObj,
        apolloData##error |> Js.Nullable.toOption,
      ) {
      | (true, _, _) => Loading
      | (false, Some(data), _) => Data(Config.parse(data))
      | (false, _, Some(error)) => Error(error)
      | (false, None, None) => NotCalled
      };
  let convertJsInputToReason = (apolloData: renderPropObjJS) => {
    result: apolloDataToReason(apolloData),
    data:
      switch (apolloData##data |> ReasonApolloUtils.getNonEmptyObj) {
      | None => None
      | Some(data) =>
        switch (Config.parse(data)) {
        | parsedData => Some(parsedData)
        | exception _ => None
        }
      },
    error: apolloData##error |> Js.Nullable.toOption,
    loading: apolloData##loading
  };
  let make =
      (
        ~variables: option(Js.Json.t)=?,
        children: (apolloSubscription, renderPropObj) => ReasonReact.reactElement,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=subscriptionComponent,
      ~props=
        Js.Nullable.(
          {
            "subscription": graphqlSubscriptionAST,
            "variables": fromOption(variables)
          }
        ),
      (subscription, apolloData) =>
      children(
        apolloSubscriptionFactory(~jsSubscription=subscription),
        convertJsInputToReason(apolloData),
      )
    );
};