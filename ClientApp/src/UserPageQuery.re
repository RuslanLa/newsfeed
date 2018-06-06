let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

[%%raw "var gql=require('graphql-tag');"];

let subscribe = [%raw
  {|
  function(subscribeToMore, refetch, userId){
    subscribeToMore(
               {
                 document: gql`subscription messageAdded($userId: ID!){
                  messageAdded(userId: $userId){
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

let make = (~userId, children) => {
  ...component,
  render: _self => {
    let postsQuery =  PostsRepository.GetPosts.make(~id=userId, ());
    <PostsRepository.GetPostsQuery variables=postsQuery##variables>
      ...(
           ({result, subscribeToMore, refetch}) => {
             subscribe(subscribeToMore, refetch, userId);
             children(Page.fromUserPostsQuery(result));
           }
         )
    </PostsRepository.GetPostsQuery>;
  }
};