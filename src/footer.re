let component = ReasonReact.statelessComponent("Footer");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self => <footer> (str("@All rights reserved")) </footer>
};