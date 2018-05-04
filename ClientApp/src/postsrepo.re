module GetPosts = [%graphql
  {|
    query getPosts($id: ID!){
        user(id: $id) {
          name,
          posts {
            content,
            date
          }
        }
    }
  |}
];

module GetPostsQuery = ReasonApollo.CreateQuery(GetPosts);