let component = ReasonReact.statelessComponent("Main");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self => {
    let message =
      Post.{
        avatar: "avatar",
        data: {
          date: "Today, 5 minutes ago",
          content: "Hello world! How are you doing?"
        }
      };
    let messages =
      List.map(_i => <Message message />, [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]);
    <section>
      <Newmessage avatar=message.avatar />
      (ReasonReact.arrayToElement(Array.of_list(messages)))
    </section>;
  }
};