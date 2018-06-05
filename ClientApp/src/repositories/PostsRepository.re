module GetPosts = [%graphql
  {|
    query getPosts($id: ID){
        user(id: $id) {
          name,
          avatar,
          followsCount,
          followersCount,
          posts {
            content,
            date
          }
        }
    }
  |}
]; /* module SubscribePosts = ReasonApolloTypes.gql("subscription messageAdded($userId: ID!) { messageAdded(userId: $userId) { content }}"); */

module GetPostsQuery = ReasonApollo.CreateQuery(GetPosts);

module GetFeed = [%graphql
  {|
  query getFeed($id:ID){
    user(id: $id) {
      name,
          avatar,
          followsCount,
          followersCount,
          feed {
            content,
            date,
            author{
              avatar
            }
          }
    }
  }
|}
];

module GetFeedQuery =
  ReasonApollo.CreateQuery(
    GetFeed
  ); /* module PostsSubscription = ReasonApollo.CreateSubscription(SubscribePosts); */

module AddPost = [%graphql
  {|
  mutation addPost($content: String!, $authorId: ID) {
    addPost(content: $content, authorId: $authorId) {
          id,
          date,
          content
      }
  }
|}
];

module AddPostMutation = ReasonApollo.CreateMutation(AddPost);