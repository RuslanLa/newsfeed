let component = ReasonReact.statelessComponent("Message");

let str = ReasonReact.stringToElement;

let make = (~message: Post.message, _children) => {
  let goToUserPage = (_event) =>{
    ReasonReact.Router.push("../user/"++message.authorId);
  };
  {
  ...component,
  render: _self => {
    let location = File.getAvatar(message.avatar);
    <div className="message">
      <img className="avatar" src=location onClick=goToUserPage/>
      <time> (str(message.data.date)) </time>
      <div className="content"> (str(message.data.content)) </div>
    </div>;
  }
};
};