let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

[%%raw "var gql=require('graphql-tag');"];

let subscribe = [%raw
  {|
  function(subscribeToMore, refetch){
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
                   "userId": "5aeedb4fbeac2104ed999c46"
                 },
                 updateQuery: (prev, cur) => {
                  refetch();
                 }
               });
              }
|}
];

let make = (~items=?, _children) => {
  ...component,
  render: _self => {
    let postsQuery =
      PostsRepository.GetPosts.make(~id="5b1165800494e237f02f2891", ());
    <PostsRepository.GetPostsQuery variables=postsQuery##variables>
      ...(
           ({result, subscribeToMore, refetch}) => {
             subscribe(subscribeToMore, refetch);
             _children(Page.fromUserPostsQuery(result));
           }
         )
    </PostsRepository.GetPostsQuery>;
  }
};