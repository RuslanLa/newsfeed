[%bs.raw {|require('./login.css')|}];
let component = ReasonReact.statelessComponent("LoginForm");

let str = ReasonReact.stringToElement;

let make = (_children) => {
    ...component,
  render: _self => <section>
  <Header /> 
  <form className="login-form">
    <div className="form-group">
       <label htmlFor ="uname">(str("Username"))</label>
       <input _type="text" placeholder="Enter Username" name="uname" required=true/>
    </div> 
    <div className="form-group">
      <label htmlFor ="psw">(str("Password"))</label>
      <input _type="password" placeholder="Enter Password" name="psw" required=true/>
    </div>
    <button _type="submit">(str("Login"))</button>
  </form>
  <Footer />
  </section>
};