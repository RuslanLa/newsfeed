let component = ReasonReact.statelessComponent("UserPage");

let make = (~userId: string, _children) => {
  ...component,
  render: _self => {
    <UserPageQuery userId> ...Content.fromPageResponse </UserPageQuery>
  }
};