'use strict';
module.exports = (sequelize, DataTypes) => {
  const Meeting = sequelize.define('Meeting', {
    team_id: DataTypes.INTEGER,
    meeting_time: DataTypes.INTEGER
  }, {});
  Meeting.associate = function(models) {
    // associations can be defined here
  };
  return Meeting;
};