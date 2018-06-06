type messageData = {
  date: string,
  content: string
};

type message = {
  avatar: string,
  authorId: string,
  data: messageData
};

let fromJsObj = obj =>
  switch obj {
  | None => {date: "", content: ""}
  | Some(post) => {date: post##date, content: post##content}
  };

let messageFromJs = obj =>
  switch obj {
  | None => {
      data: {
        date: "",
        content: ""
      },
      avatar: "",
      authorId: ""
    }
  | Some(post) => {
      data: {
        date: post##date,
        content: post##content
      },
      avatar: post##author##avatar,
      authorId:
        switch post##author##id {
        | None => ""
        | Some(data) => data
        }
    }
  };