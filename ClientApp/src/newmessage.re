let str = ReasonReact.stringToElement;

type action =
  | Focus
  | UnFocus
  | TextChange(string);

type state = {
  isFocused: bool,
  message: string
};

let component = ReasonReact.reducerComponent("NewMessage");

let make = (~avatar, _children) => {
  ...component,
  initialState: () => {isFocused: false, message: ""},
  reducer: (action, state) =>
    switch action {
    | Focus => ReasonReact.Update({...state, isFocused: true})
    | UnFocus => ReasonReact.Update({...state, isFocused: false})
    | TextChange(message) => ReasonReact.Update({...state, message})
    },
  render: self => {
    let className =
      "message new-message " ++ (self.state.isFocused ? "focused" : "");
    <PostsRepository.AddPostMutation>
      ...(
           (mutation /* Mutation to call */, _ /* Result of your mutation */) =>
             <div
               className
               onBlur=(
                 _event =>
                   if (self.state.message === "") {
                     self.send(UnFocus);
                   }
               )>
               <img className="avatar" src=(File.getAvatar(avatar)) />
               <textarea
                 placeholder="Enter new message here"
                 onFocus=(_event => self.send(Focus))
                 onChange=(
                   event =>
                     self.send(
                       TextChange(
                         ReactDOMRe.domElementToObj(
                           ReactEventRe.Form.target(event)
                         )##value
                       )
                     )
                 )
                 value=self.state.message
               />
               (
                 self.state.isFocused ?
                   <button
                     className="send rnd-btn"
                     onClick=(
                       event => {
                         Js.log(self.state.message);
                         let newPost =
                           PostsRepository.AddPost.make(
                             ~content=self.state.message,
                             ~authorId="5b1165800494e237f02f2891",
                             ()
                           );
                         mutation(
                           ~variables=newPost##variables,
                           ~refetchQueries=[|"getPosts"|],
                           ()
                         )
                         |> ignore;
                         self.send(TextChange(""));
                         self.send(UnFocus);
                       }
                     )>
                     (str("Send"))
                   </button> :
                   <div />
               )
             </div>
         )
    </PostsRepository.AddPostMutation>;
  }
};