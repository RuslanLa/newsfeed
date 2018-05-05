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
      Postsrepo.GetPosts.make(~id="5aeda07af5e4ab344917b9b1", ());
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
               let main =
                 switch response##user##posts {
                 | None =>
                   <div> (ReasonReact.stringToElement("No Data")) </div>
                 | Some(posts) =>
                   <Main
                     avatar=response##user##avatar
                     posts=(Array.map(p => Post.fromJsObj(p), posts))
                   />
                 };
               <div>
                 <Header />
                 <Aside person />
                 <Navbar items=menu />
                 main
                 <Footer />
               </div>;
             }
         )
    </Postsrepo.GetPostsQuery>;
  }
};