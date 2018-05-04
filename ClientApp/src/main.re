let component = ReasonReact.statelessComponent("Main");

let str = ReasonReact.stringToElement;

let make = (~avatar, ~posts, _children) => {
  ...component,
  render: _self => {
    let message =
      Post.{
        avatar,
        data: {
          date: "Today, 5 minutes ago",
          content: "Hello world! How are you doing?"
        }
      };
    let messages =
      Array.map(i => <Message message=Post.{avatar, data: i} />, posts);
    <section>
      <Newmessage avatar=message.avatar />
      (ReasonReact.arrayToElement(messages))
    </section>;
  }
};