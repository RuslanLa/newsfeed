let component = ReasonReact.statelessComponent("Aside");

let str = ReasonReact.stringToElement;

let toStr = count => str(string_of_int(count));

let make = (_children, ~person: User.userType) => {
  ...component,
  render: _self =>
    <aside>
      <p className="name"> (str(person.name)) </p>
      <p className="messages-count"> (toStr(person.messagesCount)) </p>
      <p className="followers"> (toStr(person.followersCount)) </p>
      <p className="follows"> (toStr(person.followsCount)) </p>
    </aside>
};