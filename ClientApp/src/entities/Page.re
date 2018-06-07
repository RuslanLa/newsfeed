open PostsRepository;

type pageStatus = {
  message: string,
  isError: bool
};

type pageData = {
  menu: array(Menuitem.menuItemType),
  person: User.userType,
  posts: MessagesBar.messageBarSetting
};

type pageResponse =
  | OK(pageData)
  | Status(pageStatus);

let fromUserPostsQuery = response =>
  switch (response, Dom.Storage.(localStorage |> getItem("user-id"))) {
  | (PostsRepository.GetPostsQuery.Loading, _) =>
    Status({message: "Loading", isError: false})
  | (Error(error: ReasonApolloTypes.apolloError), _) =>
    Status({message: "Error has happened", isError: true})
  | (Data(response), Some(userId)) =>
    let name = response##user##name;
    let person =
      User.{
        name,
        messagesCount: 3000,
        followsCount: response##user##followsCount,
        followersCount: response##user##followersCount,
        avatar: response##user##avatar
      };
    let menu = [|
      Menuitem.{title: "Profile", href: "/user"},
      Menuitem.{title: "Feed", href: "/feed"},
      Menuitem.{title: "Logout", href: "/logout"}
    |];
    switch (response##user##posts, response##user##id) {
    | (None, _) => Status({message: "Error happened", isError: true})
    | (Some(posts), Some(id)) =>
    Js.log(userId);
    Js.log(id);
    Js.log(userId == id);
    userId === id ?
      OK({menu, person, posts: MessagesBar.(MyPage(Array.map(p => Post.({
        data: fromJsObj(p), 
        avatar: person.avatar,
        authorId: switch(response##user##id){
        | None => ""
        | Some(data) => data
        }
      }), posts), person.avatar))}) : 
      OK({menu, person, posts: MessagesBar.(UserPage(Array.map(p => Post.({
        data: fromJsObj(p), 
        avatar: person.avatar,
        authorId: switch(response##user##id){
        | None => ""
        | Some(data) => data
        }
      }), posts), person.avatar))})
    };
  };

  let fromNewsFeedQuery = response =>
  switch response {
  | PostsRepository.GetFeedQuery.Loading =>
    Status({message: "Loading", isError: false})
  | Error((error: ReasonApolloTypes.apolloError)) =>
    Status({message: "Error has happened", isError: true})
  | Data(response) =>
    let name = response##user##name;
    let person =
      User.{
        name,
        messagesCount: 3000,
        followsCount: response##user##followsCount,
        followersCount: response##user##followersCount,
        avatar: response##user##avatar
      };
    let menu = [|
      Menuitem.{title: "Profile", href: "user"},
      Menuitem.{title: "Feed", href: "feed"},
      Menuitem.{title: "Logout", href: "logout"}
    |];
    switch response##user##feed {
    | None => Status({message: "Error happened", isError: true})
    | Some(posts) =>
      OK({menu, person, posts: MessagesBar.FeedPage(Array.map(p => Post.messageFromJs(p), posts))})
    };
  };