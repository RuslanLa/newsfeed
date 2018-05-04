[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self => {
    let menu = [|
      Menuitem.{title: "Profile", href: ""},
      Menuitem.{title: "Feed", href: ""},
      Menuitem.{title: "Logout", href: ""}
    |];
    let postsQuery =
      Postsrepo.GetPosts.make(~id="5ae859ee74654c100c675f5b", ());
    <Postsrepo.GetPostsQuery variables=postsQuery##variables>
      ...(
           ({result}) =>
             switch result {
             | NoData => <div> (ReasonReact.stringToElement("No Data")) </div>
             | Loading => <div> (ReasonReact.stringToElement("Loading")) </div>
             | Error(error) => <div />
             | Data(response) =>
               let name = response##user##name;
               let person =
                 User.{
                   name,
                   messagesCount: 3000,
                   followsCount: 300,
                   followersCount: 400
                 };
               <div>
                 <Header />
                 <Aside person />
                 <Navbar items=menu />
                 <Main avatar=response##user##avatar />
                 <Footer />
               </div>;
             }
         )
    </Postsrepo.GetPostsQuery>;
  }
};