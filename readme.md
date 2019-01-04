# Meeting Logger (aka meetloaf)

### "It is amazing what you can accomplish if you do not care who gets the credit." -Some Guy

## Current Status

### Frontend

Front-end client is barebones Node/React. I'm leveraging a boilerplate app that I created a while back. The application uses Webpack, Jest, SASS, and EsLint, and will be hosted separately from the Back-end API. The vision for the FE client is to be able to login to your team space, have the ability to add time (just like you would clicking the button), and visualize how much time was spent during a date timespan.

### Backend

Back-end API is Node/Express/Sequelize. It has 4 working endpoint: sign-up, sign-in, posting a meeting, and getting all meeting times. Sequelize can be used to quickly migrate the db to your local environment. Back-end API requires a PostgreSQL db. Back-end is currently running in AWS.

### IoT Device

Arduino Uno Rev 3 does not have enough memory to support Ethernet Client + ArduinoJson library. Currently waiting on more hardware (and rewriting the application to a Teensy3.2). Arduino Ethernet Shield would work fine for this but I'm going to replace it with a WIZ820io + W5500 ethernet module. These will stack perfectly on top of a Teensy. The logic to connect to AWS through Ford Proxy has been written and it works. The logic to make a call to AWS to authenticate (get a JWT token) works… it's just a matter of getting the new hardware and putting it all together (as Arduino's memory is at 80% utilization from just the authentication call.

## Installation

* Read `install.md`
