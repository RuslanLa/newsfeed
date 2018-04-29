let component = ReasonReact.statelessComponent("Message");

let str = ReasonReact.stringToElement;

let make = (~message: Post.message, _children) => {
  ...component,
  render: _self => {
    let location = File.getAvatar(message.avatar);
    <div className="message">
      <img className="avatar" src=location />
      <time> (str(message.data.date)) </time>
      <div className="content"> (str(message.data.content)) </div>
    </div>;
  }
};