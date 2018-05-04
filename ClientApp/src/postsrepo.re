module GetPosts = [%graphql
  {|
    query getPosts($id: ID!){
        user(id: $id) {
          name,
          avatar,
          posts {
            content,
            date
          }
        }
    }
  |}
];

module GetPostsQuery = ReasonApollo.CreateQuery(GetPosts);