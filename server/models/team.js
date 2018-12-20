'use strict';

var bcrypt = require('bcrypt-nodejs');

module.exports = (sequelize, DataTypes) => {
  const Team = sequelize.define('Team', {
    teamname: DataTypes.STRING,
    username: DataTypes.STRING,
    password: DataTypes.STRING
  }, {});
  Team.beforeSave((team, options) => {
    if (team.changed('password')) {
      team.password = bcrypt.hashSync(team.password, bcrypt.genSaltSync(10), null);
    }
  });
  Team.prototype.comparePassword = function (passw, cb) {
    bcrypt.compare(passw, this.password, function (err, isMatch) {
        if (err) {
            return cb(err);
        }
        cb(null, isMatch);
    });
  };
  Team.associate = function(models) {
    // associations can be defined here
  };
  return Team;
};
