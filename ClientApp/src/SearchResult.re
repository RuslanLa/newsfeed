let component = ReasonReact.statelessComponent("SearchResult");

let str = ReasonReact.stringToElement;
let goToUserPage = (userId) => ReasonReact.Router.push("../user/"++userId);
let make = (~searchCriteria, _children) => {
  ...component,
  render: _self => {
    let nav =
      <Navbar
        items=[|
          Menuitem.{title: "Profile", href: "/user"},
          Menuitem.{title: "Feed", href: "/feed"},
          Menuitem.{title: "Logout", href: "/logout"}
        |]
      />;
    let userQuery = UsersRepository.GetUsers.make(~name=searchCriteria, ());
    let section =
      <UsersRepository.GetUsersQuery variables=userQuery##variables>
        ...(
             ({result}) =>
               switch result {
               | Loading => <div> (str("Loading")) </div>
               | Error((error: ReasonApolloTypes.apolloError)) =>
                 <div> (str("Error")) </div>
               | Data(response) =>
                 let users =
                   switch response##users {
                   | Some(users) =>
                     Js.Array.map(
                      user =>
                       switch user {
                       | Some(u) =>
                         <li className="message" onClick=((_event)=>goToUserPage(u##id))>
                           <img className="avatar" src=u##avatar />
                           <div className="content"> (str(u##name)) </div>
                         </li>
                       | None => ReasonReact.nullElement},
                       users
                     )
                   | None => [||]
                   };
                 <section>
                   <ul className="searchResponse">  (ReasonReact.arrayToElement(users)) </ul>
                 </section>;
               }
           )
      </UsersRepository.GetUsersQuery>;
    ReasonReact.arrayToElement([|nav, section|]);
  }
};