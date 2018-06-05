let fromPageResponse = (pageData: Page.pageResponse) =>
  switch pageData {
  | Status(result) => <div> (ReasonReact.stringToElement("No Data")) </div>
  | OK(response) =>
    <div>
      <Header />
      <Aside person=response.person />
      <Navbar items=response.menu />
      <MessagesBar messageBarInput= response.posts />
      <Footer />
    </div>
  };