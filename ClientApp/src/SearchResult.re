let component = ReasonReact.statelessComponent("SearchResult");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self =>
  {
     let nav = <Navbar
     items=[|
       Menuitem.{title: "Profile", href: "/user"},
       Menuitem.{title: "Feed", href: "/feed"},
       Menuitem.{title: "Logout", href: "/logout"}
     |]/>;
     let section =  <section>
     <ul className="searchResponse">
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
       <li className="message">
         <img
           className="avatar"
           src="https://s3.amazonaws.com/uifaces/faces/twitter/larrybolt/128.jpg"
         />
         <div className="content"> (str("USER NAME")) </div>
       </li>
     </ul>
   </section>;
     ReasonReact.arrayToElement([|nav,section|]);
  }
};