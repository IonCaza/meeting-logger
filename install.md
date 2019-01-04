# Installing meetloaf

## Dev environment setup

* Clone repo locally
* Install PostgreSQL 11 locally and start the server
  * Login to your local PSQL instance and create a database called `meeting_logger`
  * Create a username `mlog` with password `mlog1234` (or change to match credentials in `\server\config\config.json`)
  * `GRANT ALL PRIVILEGES ON DATABASE meeting_logger TO mlog`
* Install your favorite node package manager (mine is yarn https://yarnpkg.com/en/)
* For the backend server
  * Run `yarn install` in /server
  * Run `yarn start` in /server to start the server (you shouldn't get any errors at this point)
  * To test the server, use Postman to POST to http://localhost:3000/api/signup with the following `application/json` payload
    * `{ "teamname": "MyTeam", "username": "myuser", "password": "newpassword" }` this should result in a 200 with an explanation of what was inserted into the database
* For the frontend client
  * Run `yarn install` in /client
  * Run `yarn start` in /client and you should be able to access the client at http://localhost:8080
* For the device
  * Coming soon