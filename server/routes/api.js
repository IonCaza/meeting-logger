const express = require('express');
const jwt = require('jsonwebtoken');
const passport = require('passport');
const router = express.Router();
require('../config/passport')(passport);
const Team = require('../models').Team;
const Meeting = require('../models').Meeting;

router.post('/signup', function(req, res) {
  console.log(req.body);
  if (!req.body.username || !req.body.password || !req.body.teamname) {
    res.status(400).send({msg: 'Please pass team name, username and password.'})
  } else {
    Team
      .create({
        teamname: req.body.teamname,
        username: req.body.username,
        password: req.body.password
      })
      .then((team) => res.status(201).send(team))
      .catch((error) => {
        console.log(error);
        res.status(400).send(error);
      });
  }
});

router.post('/signin', function(req, res) {
    Team
      .find({
        where: {
          username: req.body.username
        }
      })
      .then((team) => {
        if (!team) {
          return res.status(401).send({
            message: 'Authentication failed. Team not found.',
          });
        }
        team.comparePassword(req.body.password, (err, isMatch) => {
          if(isMatch && !err) {
            var token = jwt.sign(JSON.parse(JSON.stringify(team)), 'nodeauthsecret', {expiresIn: 86400 * 30});
            jwt.verify(token, 'nodeauthsecret', function(err, data){
              console.log(err, data);
            })
            res.json({success: true, token: 'JWT ' + token});
          } else {
            res.status(401).send({success: false, msg: 'Authentication failed. Wrong password.'});
          }
        })
      })
      .catch((error) => res.status(400).send(error));
});

router.get('/meeting', passport.authenticate('jwt', { session: false}), function(req, res) {
    var token = getToken(req.headers);
    if (token) {
      Meeting
        .findAll()
        .then((meetings) => res.status(200).send(meetings))
        .catch((error) => { res.status(400).send(error); });
    } else {
      return res.status(403).send({success: false, msg: 'Unauthorized.'});
    }
  });

router.post('/meeting', passport.authenticate('jwt', { session: false}), function(req, res) {
    var token = getToken(req.headers);
    if (token) {
        Meeting
            .create({
                team_id: req.body.team_id,
                meeting_time: req.body.meeting_time
            })
            .then((meetings) => res.status(201).send(meetings))
            .catch((error) => res.status(400).send(error));
    } else {
        return res.status(403).send({success: false, msg: 'Unauthorized.'});
    }
});

getToken = function (headers) {
  if (headers && headers.authorization) {
    var parted = headers.authorization.split(' ');
    if (parted.length === 2) {
      return parted[1];
    } else {
      return null;
    }
  } else {
    return null;
  }
};

module.exports = router;
