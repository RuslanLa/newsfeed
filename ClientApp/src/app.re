[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <UserPageQuery>
      ...(
           (pageData: Page.pageResponse) =>
             switch pageData {
             | Status(result) =>
               <div> (ReasonReact.stringToElement("No Data")) </div>
             | OK(response) =>
               <div>
                 <Header />
                 <Aside person=response.person />
                 <Navbar items=response.menu />
                 <Main avatar=response.person.avatar posts=response.posts />
                 <Footer />
               </div>
             }
         )
    </UserPageQuery>
};