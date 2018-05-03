module GetPosts = [%graphql
  {|
    query getPosts($id: String!){
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