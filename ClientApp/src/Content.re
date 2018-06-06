let fromPageResponse = (pageData: Page.pageResponse) =>
  switch pageData {
  | Status(result) => <div> (ReasonReact.stringToElement("No Data")) </div>
  | OK(response) =>
    let aside = <Aside person=response.person />;
    let navbar = <Navbar items=response.menu />;
    let messageBar = <MessagesBar messageBarInput=response.posts />;
    ReasonReact.arrayToElement([|aside, navbar, messageBar|]);
  };