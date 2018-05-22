open PostsRepository;

type pageStatus = {
  message: string,
  isError: bool
};

type pageData = {
  menu: array(Menuitem.menuItemType),
  person: User.userType,
  posts: array(Post.messageData)
};

type pageResponse =
  | OK(pageData)
  | Status(pageStatus);

let fromUserPostsQuery = response =>
  switch response {
  | PostsRepository.GetPostsQuery.NoData =>
    Status({message: "No response", isError: true})
  | Loading => Status({message: "Loading", isError: false})
  | Error(error: ReasonApolloTypes.apolloError) => Status({message: "Error has happened", isError: true})
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
      Menuitem.{title: "Profile", href: ""},
      Menuitem.{title: "Feed", href: ""},
      Menuitem.{title: "Logout", href: ""}
    |];
      switch response##user##posts {
      | None => Status({message: "Error happened", isError: true})
      | Some(posts) =>OK(
        {
          menu,
          person,
          posts: Array.map(p => Post.fromJsObj(p), posts)
        });
      };
  };