let component = ReasonReact.statelessComponent("Aside");

let str = ReasonReact.stringToElement;

let make = (_children) => {
    ...component,
    render: (_self) => 
    <aside>
            <p className="name">(str("Ruslan Latypov"))</p>
            <p className="messages-count">(str("200"))</p>
            <p className="followers">(str("200"))</p>
            <p className="follows">(str("200"))</p>
    </aside>
};