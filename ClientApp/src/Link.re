let component = ReasonReact.statelessComponent("Link");

let str = ReasonReact.stringToElement;

let make = (~href:string, _children: ReasonReact.reactElement) => {
  let click = event => {
    ReasonReact.Router.push(
      ReactDOMRe.domElementToObj(ReactEventRe.Mouse.target(event))##href
    );
    ReactEventRe.Mouse.preventDefault(event);
  };
  {...component, render: _self => <a href=href onClick=click> _children </a>};
};