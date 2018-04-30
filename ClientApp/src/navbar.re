let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

let make = (~items=?, _children) => {
  ...component,
  render: _self => {
    let listElements =
      ReasonReact.arrayToElement(
        Array.map(
          (i: Menuitem.menuItemType) =>
            <li> <a href=i.href> (str(i.title)) </a> </li>,
          switch items {
          | Some(elements) => elements
          | None => [||]
          }
        )
      );
    <nav> <ul> listElements </ul> </nav>;
  }
};