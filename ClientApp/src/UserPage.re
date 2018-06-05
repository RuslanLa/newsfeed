[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("UserPage");

let make = (~userId: option(string), _children) => {
  ...component,
  render: _self => {
    <UserPageQuery userId> ...Content.fromPageResponse </UserPageQuery>
  }
};