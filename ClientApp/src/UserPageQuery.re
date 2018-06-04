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

let make = (~userId, _children) => {
  ...component,
  render: _self => {
    let postsQuery = switch userId {
    | Some(id) => PostsRepository.GetPosts.make(~id=id, ())
    | None => PostsRepository.GetPosts.make(())
    };
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