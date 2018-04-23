let component = ReasonReact.statelessComponent("Main");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self => {
    let messages =
      List.map(_i => <Message />, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    <section>
      <Newmessage />
      (ReasonReact.arrayToElement(Array.of_list(messages)))
    </section>;
  }
};