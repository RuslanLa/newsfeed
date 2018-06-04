
let str = ReasonReact.stringToElement;

type route =
  | Login
  | UserPage(option(string));

type action =
  | ChangeRoute(route);

type state = {route: route};
let component = ReasonReact.reducerComponent("AppRouter");

let resolveRoute = (url) =>  switch (url, Dom.Storage.(localStorage |> getItem("token"))) {
    | ([], Some(token)) => UserPage(None)
    | (["user", id], Some(userId)) => UserPage(Some(id))
    | (["login"], None) => Login
    | ([], None) => Login
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
      ReasonReact.Update({ route: resolveRoute([])});
  },
  render: self => switch (self.state.route) {
    | UserPage(id) => <UserPage userId=id/>
    | Login => <LoginForm />
  }
};