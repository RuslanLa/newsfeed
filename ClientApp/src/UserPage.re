[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("UserPage");

let fromPageResponse = (pageData: Page.pageResponse) =>
  switch pageData {
  | Status(result) => <div> (ReasonReact.stringToElement("No Data")) </div>
  | OK(response) =>
    <div>
      <Header />
      <Aside person=response.person />
      <Navbar items=response.menu />
      <Main avatar=response.person.avatar posts=response.posts />
      <Footer />
    </div>
  };

let make = (~userId: option(string), _children) => {
  ...component,
  render: _self => <UserPageQuery userId> ...fromPageResponse </UserPageQuery>
};