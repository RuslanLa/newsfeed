[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self => {
    let person =
      User.{
        name: "Ruslan Latypov",
        messagesCount: 3000,
        followsCount: 300,
        followersCount: 400
      };
    let menu = [|
      Menuitem.{title: "Profile", href: ""},
      Menuitem.{title: "Feed", href: ""},
      Menuitem.{title: "Logout", href: ""}
    |];
    <div>
      <Header />
      <Aside person />
      <Navbar items=menu />
      <Main />
      <Footer />
    </div>;
  }
};