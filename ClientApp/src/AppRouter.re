[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

type route =
  | Login
  | UserPage(string)
  | NewsFeed(string)
  | Search
  | Logout;

type action =
  | ChangeRoute(route);

type state = {route};

let component = ReasonReact.reducerComponent("AppRouter");

let resolveRoute = url => {
  Js.log(">>>>>>>>>>>>>>>>>>>>>>>>>>><>>>>>>>>>>>>>>>>>>>>>>");
  Js.log(url);
  switch (
    url,
    Dom.Storage.(localStorage |> getItem("token")),
    Dom.Storage.(localStorage |> getItem("user-id"))
  ) {
  | (["user", id], Some(token), _) => UserPage(id)
  | (["login"], None, _) => Login
  | (["logout"], Some(token), _) =>
    Js.log(">>>>>>>>>>>>>>>>>>>>>>>here");
    Dom.Storage.(localStorage |> removeItem("token"));
    Dom.Storage.(localStorage |> removeItem("user-id"));
    ReasonReact.Router.push("login");
    Login;
  | (["user"], Some(token), Some(id)) => UserPage(id)
  | (["search"], _, _) => Search
  | (_, Some(token), Some(id)) => NewsFeed(id)
  | (_, _, _) => Login
  };
};

let make = _children => {
  ...component,
  reducer: (action: action, state: state) =>
    switch action {
    | ChangeRoute(route) => ReasonReact.Update({route: route})
    },
  initialState: () => {route: Login},
  didMount: self => {
    ReasonReact.Router.watchUrl(url =>
      self.send(ChangeRoute(resolveRoute(url.path)))
    );
    ReasonReact.Update({
      route: resolveRoute(ReasonReact.Router.dangerouslyGetInitialUrl().path)
    });
  },
  render: self => {
    let content =
      switch self.state.route {
      | UserPage(id) => <UserPage userId=id />
      | NewsFeed(id) => <NewsFeed userId=id />
      | Search => <SearchResult />
      | Login => <LoginForm />
      };
    <div> <Header /> (content) <Footer /> </div>;
  }
};