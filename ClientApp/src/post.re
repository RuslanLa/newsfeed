type messageData = {
  date: string,
  content: string
};

type message = {
  avatar: string,
  data: messageData
};

let fromJsObj = obj =>
  switch obj {
  | None => {date: "", content: ""}
  | Some(post) => {date: post##date, content: post##content}
  };