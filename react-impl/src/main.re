let component = ReasonReact.statelessComponent("Main");

let str = ReasonReact.stringToElement;

let make = (_children) => {
    ...component,
    render: (_self) => 
    <section>
    <Message></Message>
  </section>
};