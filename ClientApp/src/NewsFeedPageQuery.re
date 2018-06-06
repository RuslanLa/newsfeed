let component = ReasonReact.statelessComponent("NewsFeedPage");

let str = ReasonReact.stringToElement;

[%%raw "var gql=require('graphql-tag');"];
[%%raw "var gql=require('graphql-tag');"];

let subscribe = [%raw
  {|
  function(subscribeToMore, refetch, userId){
    subscribeToMore(
               {
                 document: gql`subscription messageAddedToTheNewsFeed($userId: ID!){
                  messageAddedToTheNewsFeed(userId: $userId){
                    content,
                    date,
                    id
                  }
                }`,
                 variables: {
                   "userId": userId
                 },
                 updateQuery: (prev, cur) => {
                  refetch();
                 }
               });
              }
|}
];

let make = (~userId, _children) => {
  ...component,
  render: _self => {
    let postsQuery = switch userId {
    | Some(id) => PostsRepository.GetFeed.make(~id=id, ())
    | None => PostsRepository.GetFeed.make(())
    };
    <PostsRepository.GetFeedQuery variables=postsQuery##variables>
      ...(
           ({result, subscribeToMore, refetch}) => {
            subscribe(subscribeToMore, refetch, userId);
            _children(Page.fromNewsFeedQuery(result));
          }
         )
    </PostsRepository.GetFeedQuery>;
  }
};