var passport = require("passport");
var passportJWT = require("passport-jwt");
const User = require("./models/user");

var ExtractJwt = passportJWT.ExtractJwt;
var JwtStrategy = passportJWT.Strategy;
ExtractJwt.fr

var jwtOptions = {}
jwtOptions.jwtFromRequest = ExtractJwt.fromExtractors([ExtractJwt.fromAuthHeaderAsBearerToken(), ExtractJwt.fromUrlQueryParameter('auth_token')]);
jwtOptions.secretOrKey = 'tasmanianDevil';

var strategy = new JwtStrategy(jwtOptions, function (jwt_payload, next) {
    User.findById(jwt_payload.id, (err, user) => {
        if (user) {
            next(null, user);
            return;
        }
        next(null, false);
    });
});

passport.use(strategy);

module.exports = { passport: passport, jwtOptions: jwtOptions };