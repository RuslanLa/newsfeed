// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Message = require("./message.js");
var Newmessage = require("./newmessage.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");

var component = ReasonReact.statelessComponent("Main");

function str(prim) {
  return prim;
}

function make() {
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
              var messages = List.map((function () {
                      return ReasonReact.element(/* None */0, /* None */0, Message.make(/* record */[
                                      /* avatar */"avatar",
                                      /* data : record */[
                                        /* date */"Today, 5 minutes ago",
                                        /* content */"Hello world! How are you doing?"
                                      ]
                                    ], /* array */[]));
                    }), /* :: */[
                    0,
                    /* :: */[
                      1,
                      /* :: */[
                        2,
                        /* :: */[
                          3,
                          /* :: */[
                            4,
                            /* :: */[
                              5,
                              /* :: */[
                                6,
                                /* :: */[
                                  7,
                                  /* :: */[
                                    8,
                                    /* :: */[
                                      9,
                                      /* :: */[
                                        10,
                                        /* [] */0
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ]
                        ]
                      ]
                    ]
                  ]);
              return React.createElement("section", undefined, ReasonReact.element(/* None */0, /* None */0, Newmessage.make("avatar", /* array */[])), $$Array.of_list(messages));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.str = str;
exports.make = make;
/* component Not a pure module */