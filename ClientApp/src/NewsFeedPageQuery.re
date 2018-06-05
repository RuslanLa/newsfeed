let component = ReasonReact.statelessComponent("NewsFeedPage");

let str = ReasonReact.stringToElement;

[%%raw "var gql=require('graphql-tag');"];


let make = (~userId, _children) => {
  ...component,
  render: _self => {
    let postsQuery = switch userId {
    | Some(id) => PostsRepository.GetFeed.make(~id=id, ())
    | None => PostsRepository.GetFeed.make(())
    };
    <PostsRepository.GetFeedQuery variables=postsQuery##variables>
      ...(
           ({result}) => {
             _children(Page.fromNewsFeedQuery(result));
           }
         )
    </PostsRepository.GetFeedQuery>;
  }
};