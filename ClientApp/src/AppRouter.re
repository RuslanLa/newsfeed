
let str = ReasonReact.stringToElement;

type route =
  | Login
  | UserPage(option(string))
  | Logout;

type action =
  | ChangeRoute(route);

type state = {route: route};
let component = ReasonReact.reducerComponent("AppRouter");

let resolveRoute = (url) => {
  Js.log(">>>>>>>>>>>>>>>>>>>>>>>>>>><>>>>>>>>>>>>>>>>>>>>>>");
  Js.log(url);
  switch (url, Dom.Storage.(localStorage |> getItem("token"))) {
    | (["user", id], Some(token)) => UserPage(Some(id))
    | (["login"], None) => Login
    | (["logout"], Some(token)) => {
      Js.log(">>>>>>>>>>>>>>>>>>>>>>>here");
      Dom.Storage.(localStorage |> removeItem("token"));
      ReasonReact.Router.push("login");
      Login;
    }
    | ([], Some(token)) => UserPage(None)
    | ([], None) => Login
    };
  };
let make = (_children) => {
  ...component,
  reducer: (action: action, state: state) =>
  switch action {
  | ChangeRoute(route) => ReasonReact.Update({ route: route})
  },
  initialState: () => {route: Login},
  didMount: self => {
      ReasonReact.Router.watchUrl(url => self.send(ChangeRoute(resolveRoute(url.path)))
      );
      ReasonReact.Update({ route: resolveRoute(ReasonReact.Router.dangerouslyGetInitialUrl().path)});
  },
  render: self => switch (self.state.route) {
    | UserPage(id) => <UserPage userId=id/>
    | Login => <LoginForm />
  }
};