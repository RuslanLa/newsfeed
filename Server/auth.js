const User = require("./models/user");
const { jwtOptions } = require("./passport-config");
var jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');

async function authorize(name, password) {
    const user = await User.findOne({
        name: name
    }).exec();
    if (!user) {
        return null;
    }
    if (bcrypt.compareSync(password, user.password)) {
        const payload = { id: user.id };
        const token = jwt.sign(payload, jwtOptions.secretOrKey);
        return token;
    }
}

module.exports = {
    authorizeUser: authorize
};