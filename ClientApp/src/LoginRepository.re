type loginResponse = {
    id: string,
    token: string,
    message: string
};

type state =
  | NotAsked
  | Loading
  | Failure
  | Success(loginResponse);

module Decode = {
    let loginResponse = response =>
      Json.Decode.{
        id: field("id", string, response),
        token: field("token", string, response),
        message: field("message", string, response)
      };
  };
  type userInfo = {
    login: string,
    password: string
  };
  let encodeUserInfo:(userInfo)=>Js.Json.t = (m: userInfo) => Json.Encode.(object_([("name", string(m.login)), ("password", string(m.password))]));

  let sendLogin = (data: userInfo) =>
  Js.Promise.(
    Fetch.fetchWithInit(Url.Consts.loginUrl, Fetch.RequestInit.make(
      ~method_=Post,
      ~body=Fetch.BodyInit.make(Js.Json.stringify(encodeUserInfo(data))),
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      ()
    ))
    |> then_(Fetch.Response.json)
    |> then_(json =>
         json |> Decode.loginResponse |> (loginResponse => Some(loginResponse) |> resolve)
       )
    |> catch(_err => resolve(None))
  );