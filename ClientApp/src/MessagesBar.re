let component = ReasonReact.statelessComponent("Main");

let str = ReasonReact.stringToElement;

type messageBarSetting =
  | UserPage(array(Post.message), string)
  | FeedPage(array(Post.message));

let make = (~messageBarInput, _children) => {
  ...component,
  render: _self => {
    let mapMessages = messages => Array.map(message => <Message message />, messages);
    let (messages, newMessage) =
      switch messageBarInput {
      | UserPage(messages, avatar) => (
          mapMessages(messages),
          <Newmessage avatar />
        )
      | FeedPage(newsFeed) => (
          mapMessages(newsFeed),
          ReasonReact.nullElement
        )
      };
    <section> newMessage (ReasonReact.arrayToElement(messages)) </section>;
  }
};