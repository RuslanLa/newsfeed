module GetUsers= [%graphql
  {|
    query getUsers($name: String!){
        users(name: $name) {
          name,
          id,
          avatar
        }
    }
  |}
];

module GetUsersQuery = ReasonApollo.CreateQuery(GetUsers);