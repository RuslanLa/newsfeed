let component = ReasonReact.statelessComponent("Message");

let str = ReasonReact.stringToElement;

[@bs.module] external avatar : string = "./imgs/logo.svg";

let make = (_children) => {
    ...component,
    render: (_self) => 
    <div className="message new-message">
      <img className="avatar" src=avatar />
      <textarea placeholder="Enter new message here"></textarea>
      <button className="send rnd-btn">(str("Send"))</button>
    </div>
};