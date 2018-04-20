let component = ReasonReact.statelessComponent("Navbar");

let str = ReasonReact.stringToElement;

let make = (_children) => {
    ...component,
    render: (_self) => 
    <nav>
            <ul>
                <li>
                    <a href="#">(str("Profile"))</a>
                </li>
                <li>
                    <a href="#">(str("Feed"))</a>
                </li>
                <li>
                    <a href="#">(str("Logout"))</a>
                </li>
            </ul>
    </nav>
};