let str = ReasonReact.stringToElement;

type action =
  | Focus
  | UnFocus
  | TextChange(string);

type state = {isFocused: bool, message: string};

let component = ReasonReact.reducerComponent("NewMessage");

let make = (~avatar, _children) => {
  ...component,
  initialState: () => {isFocused: false, message: ""},
  reducer: (action, state) =>
    switch action {
    | Focus => ReasonReact.Update({...state, isFocused: true})
    | UnFocus => ReasonReact.Update({...state, isFocused: false})
    | TextChange(message) => ReasonReact.Update({...state, message })
    },
  render: self =>{
    let className = "message new-message " ++ (self.state.isFocused?"focused":"");
    <Postsrepo.AddPostMutation>
    ...((
      mutation /* Mutation to call */, 
      _ /* Result of your mutation */
    ) => {
        <div className=className>
      <img className="avatar" src=(File.getAvatar(avatar)) />
      <textarea
        placeholder="Enter new message here"
        onFocus=(_event => self.send(Focus))
        onChange=(event => self.send(TextChange(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value)))
        value=self.state.message
      />
      (self.state.isFocused ? <button className="send rnd-btn" onClick=((event)=>{
        Js.log(self.state.message);
        let newPost = Postsrepo.AddPost.make(~content=self.state.message, ~authorId="5ae8597d1a1e470158163421", ());
        mutation(~variables=newPost##variables, ~refetchQueries=[|"getPosts"|], 
        ()) |> ignore;
        self.send(TextChange(""));
      })> (str("Send")) </button>:<div/>)
    </div>
    })
    </Postsrepo.AddPostMutation>
  }
};