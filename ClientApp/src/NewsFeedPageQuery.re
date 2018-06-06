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
    let postsQuery = PostsRepository.GetFeed.make(~id=userId, ());
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