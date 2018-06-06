[%bs.raw {|require('./login.css')|}];

open LoginRepository;

type action =
  | Login(string)
  | Password(string)
  | Send
  | LoggedIn(loginResponse)
  | LoginFailed;
type formState =
  | Sending
  | Success
  | Error
  | None;

type state = {
  login: string,
  password: string,
  formState
};

let component = ReasonReact.reducerComponent("LoginForm");

let str = ReasonReact.stringToElement;

let textFromEvent = event => ReactDOMRe.domElementToObj(
                               ReactEventRe.Form.target(event)
                             )##value;

let sendLoginRequest = (send, data: userInfo) => {
  Js.Promise.(
              sendLogin(data)
              |> then_(result =>
                   switch (result) {
                   | Some(loginResponse) =>
                      resolve(send(LoggedIn(loginResponse)))
                   | None => resolve(send(LoginFailed))
                   }
                 )
              |> ignore
            )
};

let make = _children => {
  ...component,
  initialState: () => {login: "", password: "", formState: None},
  reducer: (action: action, state: state) =>
    switch action {
    | Login(value) => ReasonReact.Update({...state, login: value})
    | Password(value) => ReasonReact.Update({...state, password: value})
    | Send =>
      ReasonReact.UpdateWithSideEffects(
        {...state, formState: Sending},
        (self => sendLoginRequest(self.send, {
          login: self.state.login,
          password: self.state.password
        }))
      )
    | LoggedIn(data) => ReasonReact.SideEffects((self)=>{
      Dom.Storage.(localStorage |> setItem("token", data.token));
      Dom.Storage.(localStorage |> setItem("user-id", data.id));
      ReasonReact.Router.push("/user/"++data.id);
    })
    |LoginFailed => ReasonReact.Update({...state, formState: Error})
    },
  render: self =>
    <section>
      <Header />
      <form className="login-form">
        <div className="form-group">
          <label htmlFor="uname"> (str("Username")) </label>
          <input
            _type="text"
            onChange=(event => self.send(Login(textFromEvent(event))))
            value=self.state.login
            placeholder="Enter Username"
            name="uname"
            required=true
          />
        </div>
        <div className="form-group">
          <label htmlFor="psw"> (str("Password")) </label>
          <input
            _type="password"
            onChange=(event => self.send(Password(textFromEvent(event))))
            value=self.state.password
            placeholder="Enter Password"
            name="psw"
            required=true
          />
        </div>
        <button
          onClick=(
            event => {
              ReactEventRe.Mouse.preventDefault(event);
              self.send(Send);
            }
          )>
          (str("Login"))
        </button>
      </form>
      <Footer />
    </section>
};