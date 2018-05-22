let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

let make = (~items=?, _children) => {
  ...component,
  render: _self => {
    let postsQuery =
      PostsRepository.GetPosts.make(~id="5aeedb4fbeac2104ed999c46", ());
    <PostsRepository.GetPostsQuery variables=postsQuery##variables>
      ...(({result}) => _children(Page.fromUserPostsQuery(result)))
    </PostsRepository.GetPostsQuery>;
  }
};