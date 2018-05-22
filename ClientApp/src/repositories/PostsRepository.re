module GetPosts = [%graphql
  {|
    query getPosts($id: ID!){
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
];

module GetPostsQuery = ReasonApollo.CreateQuery(GetPosts);

module AddPost = [%graphql
  {|
  mutation addPost($content: String!, $authorId: ID!) {
    addPost(content: $content, authorId: $authorId) {
          id,
          date,
          content
      }
  }
|}
];

module AddPostMutation = ReasonApollo.CreateMutation(AddPost);