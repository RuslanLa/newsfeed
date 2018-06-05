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
  switch response {
  | PostsRepository.GetPostsQuery.Loading =>
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
      Menuitem.{title: "Profile", href: "/user"},
      Menuitem.{title: "Feed", href: "/feed"},
      Menuitem.{title: "Logout", href: "/logout"}
    |];
    switch response##user##posts {
    | None => Status({message: "Error happened", isError: true})
    | Some(posts) =>
      OK({menu, person, posts: MessagesBar.(UserPage(Array.map(p => Post.({
        data: fromJsObj(p), 
        avatar: person.avatar
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