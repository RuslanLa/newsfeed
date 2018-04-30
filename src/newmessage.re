let component = ReasonReact.statelessComponent("NewMessage");

let str = ReasonReact.stringToElement;

/* [@bs.module] external avatar : string = "./imgs/avatar.jpg"; */
let make = (~avatar, _children) => {
  ...component,
  render: _self =>
    <div className="message new-message">
      <img className="avatar" src=(File.getAvatar(avatar)) />
      <textarea placeholder="Enter new message here" />
      <button className="send rnd-btn"> (str("Send")) </button>
    </div>
};