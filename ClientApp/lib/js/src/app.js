// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var Main = require("./main.js");
var Aside = require("./aside.js");
var React = require("react");
var Footer = require("./footer.js");
var Header = require("./header.js");
var Navbar = require("./navbar.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

((require('./app.css')));

var component = ReasonReact.statelessComponent("App");

function make(_, _$1) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var menu = /* array */[
                /* record */[
                  /* title */"Profile",
                  /* href */""
                ],
                /* record */[
                  /* title */"Feed",
                  /* href */""
                ],
                /* record */[
                  /* title */"Logout",
                  /* href */""
                ]
              ];
              return React.createElement("div", undefined, ReasonReact.element(/* None */0, /* None */0, Header.make(/* array */[])), ReasonReact.element(/* None */0, /* None */0, Aside.make(/* array */[], /* record */[
                                  /* name */"Ruslan Latypov",
                                  /* messagesCount */3000,
                                  /* followersCount */400,
                                  /* followsCount */300
                                ])), ReasonReact.element(/* None */0, /* None */0, Navbar.make(/* Some */[menu], /* array */[])), ReasonReact.element(/* None */0, /* None */0, Main.make(/* array */[])), ReasonReact.element(/* None */0, /* None */0, Footer.make(/* array */[])));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.make = make;
/*  Not a pure module */