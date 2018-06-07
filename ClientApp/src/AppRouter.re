[%bs.raw {|require('./app.css')|}];

let str = ReasonReact.stringToElement;

type route =
  | Login
  | UserPage(string)
  | NewsFeed(string)
  | Search
  | Logout;

type action =
  | ChangeRoute(route)
  | Search(string);

type state = {
  route,
  searchCriteria: string
};

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
    | ChangeRoute(route) => ReasonReact.Update({route, searchCriteria: ""})
    | Search(name) =>
      switch name {
      | "" =>
        ReasonReact.Update({
          route:
            resolveRoute(ReasonReact.Router.dangerouslyGetInitialUrl().path),
          searchCriteria: ""
        })
      | name => ReasonReact.Update({route: Search, searchCriteria: name})
      }
    },
  initialState: () => {route: Login, searchCriteria: ""},
  didMount: self => {
    ReasonReact.Router.watchUrl(url =>
      self.send(ChangeRoute(resolveRoute(url.path)))
    );
    ReasonReact.Update({
      route: resolveRoute(ReasonReact.Router.dangerouslyGetInitialUrl().path),
      searchCriteria: ""
    });
  },
  render: self => {
    let content =
      switch self.state.route {
      | UserPage(id) => <UserPage userId=id />
      | NewsFeed(id) => <NewsFeed userId=id />
      | Search => <SearchResult searchCriteria=self.state.searchCriteria/>
      | Login => <LoginForm />
      };
    <div>
      <Header
        searchValue=self.state.searchCriteria
        searchOnChange=(
          event =>
            self.send(
              Search(
                ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
              )
            )
        )
      />
      content
      <Footer />
    </div>;
  }
};