let component = ReasonReact.statelessComponent("Message");

let str = ReasonReact.stringToElement;

[@bs.module] external avatar : string = "./imgs/avatar.jpg";

let make = _children => {
  ...component,
  render: _self =>
    <div className="message">
      <img className="avatar" src=avatar />
      <time> (str("Today, 5 mins ago")) </time>
      <div className="content"> (str("Hello world! How are you?")) </div>
    </div>
};