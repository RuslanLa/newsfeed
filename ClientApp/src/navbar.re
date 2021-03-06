let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

let make = (~items=?, _children) => {
  let click = (event) => {
    ReasonReact.Router.push(ReactDOMRe.domElementToObj(
                           ReactEventRe.Mouse.target(event)
    )##href);
    ReactEventRe.Mouse.preventDefault(event);
  };
  {
  ...component,
  render: _self => {
    let listElements =
      ReasonReact.arrayToElement(
        Array.map(
          (i: Menuitem.menuItemType) =>
            <li> <Link href=i.href> ...(str(i.title)) </Link> </li>,
          switch items {
          | Some(elements) => elements
          | None => [||]
          }
        )
      );
    <nav> <ul> listElements </ul> </nav>;
  }
};
};