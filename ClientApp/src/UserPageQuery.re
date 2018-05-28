let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

[%%raw "var gql=require('graphql-tag');"];

let subscribe = [%raw
  {|
  function(subscribeToMore){
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
                   console.log("UPDATE!!!!!!!!!!!", prev, cur);
                   let user = Object.assign({}, prev.user);
                   user.posts = user.posts.concat([]);
                   if(user.posts.find(u=>u.id==cur.subscriptionData.data.messageAdded.id)){
                     return prev;
                   }
                   user.posts = [cur.subscriptionData.data.messageAdded].concat(prev.user.posts);
                   console.log(">>>>>>>", user);
                   let result = Object.assign({}, prev);
                   result.user = user;
                   console.log(result);
                   return result;
                 }
               });
              }
|}
];

let make = (~items=?, _children) => {
  ...component,
  render: _self => {
    let postsQuery =
      PostsRepository.GetPosts.make(~id="5aeedb4fbeac2104ed999c46", ());
    <PostsRepository.GetPostsQuery variables=postsQuery##variables>
      ...(
           ({result, subscribeToMore}) => {
             subscribe(subscribeToMore);
             _children(Page.fromUserPostsQuery(result));
           }
         )
    </PostsRepository.GetPostsQuery>;
  }
};