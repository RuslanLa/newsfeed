let component = ReasonReact.statelessComponent("Header");

let str = ReasonReact.stringToElement;

let make = _children => {
  ...component,
  render: _self =>
    <header>
      <div className="title"> <a href="#"> (str("The Newsfeed")) </a> </div>
      <input _type="search" placeholder="Search" />
      <ul className="icons socialicons">
        <li> <a className="twitterb" href="#" /> </li>
        <li> <a className="instagram" href="#" /> </li>
      </ul>
    </header>
};