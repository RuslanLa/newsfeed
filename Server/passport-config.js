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
    console.log('payload received', jwt_payload);
    const user = User.findById(jwt_payload.id);
    if (user) {
        next(null, user);
    } else {
        next(null, false);
    }
});

passport.use(strategy);

module.exports = { passport: passport, jwtOptions: jwtOptions };