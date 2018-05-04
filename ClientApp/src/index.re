[%bs.raw {|require('./index.css')|}];

[%bs.raw {|require('./medium.css')|}];

[%bs.raw {|require('./large.css')|}];

[@bs.module "./registerServiceWorker"]
external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(
  <ReasonApollo.Provider client=Client.instance>
    <App message="Welcome to React and Reason" />
  </ReasonApollo.Provider>,
  "root"
);

register_service_worker();