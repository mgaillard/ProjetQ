// Get dependencies
const express = require('express');
const path = require('path');
const http = require('http');
var MongoClient = require('mongodb').MongoClient;

const config = require('./server/config').Config;

// Get our API routes
const api = require('./server/routes/api');

const app = express();

// Point static path to dist
app.use(express.static(path.join(__dirname, 'dist')));

// Set our api routes
app.use('/api', api);

// Catch all other routes and return the index file
app.get('*', (req, res) => {
  res.sendFile(path.join(__dirname, 'dist/index.html'));
});

// Run the api if the connection to MongoDB is sucessful
MongoClient.connect(config.database.url, { promiseLibrary: Promise })
  .catch(err => console.error(err.stack))
  .then(db => {
    app.locals.db = db;
    app.locals.config = config;
    app.listen(config.application.port, () => {
      console.log(`Node.js app is listening at http://localhost:${config.application.port}`);
    });
  });
