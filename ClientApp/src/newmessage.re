let str = ReasonReact.stringToElement /* [@bs.module] external avatar : string = "./imgs/avatar.jpg"; */;

type action =
  | Focus
  | UnFocus;

type state = {isFocused: bool};

let component = ReasonReact.reducerComponent("NewMessage");

let make = (~avatar, _children) => {
  ...component,
  initialState: () => {isFocused: false},
  reducer: (action, _state) =>
    switch action {
    | Focus => ReasonReact.Update({isFocused: true})
    | UnFocus => ReasonReact.Update({isFocused: false})
    },
  render: self =>{
    let className = "message new-message " ++ (self.state.isFocused?"focused":"");
    <div className=className>
      <img className="avatar" src=(File.getAvatar(avatar)) />
      <textarea
        placeholder="Enter new message here"
        onFocus=(_event => self.send(Focus))
        onBlur=(_event=>self.send(UnFocus))
      />
      (self.state.isFocused?      <button className="send rnd-btn"> (str("Send")) </button>
:<div/>      )
    </div>
  }
};