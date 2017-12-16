const express = require('express');
var validUrl = require('valid-url');
var rp = require('request-promise');
var Long = require('mongodb').Long;
const url = require('url');

const router = express.Router();

function CheckUrlValidity(query_url) {
  if (validUrl.isUri(query_url)) {
    return Promise.resolve(query_url);
  } else {
    return Promise.reject('Invalid query url.');
  }
}

function MakeHashImage(hash_image_url) {
  return function (query_url) {
    const hash_api_call_options = {
      method: 'GET',
      url: hash_image_url,
      qs: {
        url: query_url
      },
      json: true
    };

    return rp(hash_api_call_options);
  };
}

function MakeSearchHashByRadius(search_radius_url, radius) {
  return function (hash_api_result) {
    const search_api_call_options = {
      method: 'GET',
      url: search_radius_url,
      qs: {
        query_hash: hash_api_result.dct_hash,
        radius: radius
      },
      json: true
    };

    return rp(search_api_call_options);
  };
}

function MakeSearchHashByKNearest(search_knearest_url, k) {
  return function (hash_api_result) {
    const search_api_call_options = {
      method: 'GET',
      url: search_knearest_url,
      qs: {
        query_hash: hash_api_result.dct_hash,
        k: k
      },
      json: true
    };

    return rp(search_api_call_options);
  };
}

function MakeSearchImagesInDatabase(db, collection_name) {
  return function (search_api_result) {
    // Convert hash in api result from string to Long
    for (let i = 0; i < search_api_result.length; i++) {
      search_api_result[i].hash = Long.fromString(search_api_result[i].hash);
    }

    // Extract the hashes from the API result.
    var hashes = new Set();
    for (let i = 0; i < search_api_result.length; i++) {
      hashes.add(search_api_result[i].hash);
    }

    return new Promise(function (resolve, reject) {
      var collection = db.collection(collection_name);
      // Find images by hash
      collection.find({ 'dct_hash': { $in: [...hashes] } }).toArray(function (err, docs) {
        if (err === null) {
          var results = [];

          // Add the url to the search results
          // For each search result
          for (let i = 0; i < search_api_result.length; i++) {
            // For each image retrieved from the database
            for (let j = 0; j < docs.length; j++) {
              // If the image hash is the same as the search result hash
              if (search_api_result[i].hash.equals(docs[j].dct_hash)) {
                // The image is a result to the query for this distance
                const doc_url = url.parse(docs[j].url);

                results.push({
                  distance: search_api_result[i].distance,
                  url: doc_url.href,
                  url_domain: doc_url.hostname,
                  url_pathname: doc_url.pathname
                });
              }
            }
          }
          resolve(results);
        } else {
          reject(err);
        }
      });
    });
  };
}

router.get('/search', function (req, res) {
  const db = req.app.locals.db;
  const app_config = req.app.locals.config;

  // By default, the serach method is radius
  var method = 'radius';
  // Allowed search methods
  if (req.query.method === 'radius' || req.query.method === 'knearest') {
    method = req.query.method;
  }

  var HashImage = MakeHashImage(app_config.index.hash_image_url);
  var SearchHash;
  if (method === 'radius') {
    SearchHash = MakeSearchHashByRadius(app_config.index.search_radius_url, app_config.index.default_radius);
  } else if (method === 'knearest') {
    SearchHash = MakeSearchHashByKNearest(app_config.index.search_knearest_url, app_config.index.default_k);
  }
  var SearchImagesInDatabase = MakeSearchImagesInDatabase(db, app_config.database.collection);

  CheckUrlValidity(req.query.url)
    .then(HashImage)
    .then(SearchHash)
    .then(SearchImagesInDatabase)
    .then(function (image_results) {
      var result = {
        query_url: req.query.url,
        results: image_results
      };

      res.setHeader('Content-Type', 'application/json');
      res.end(JSON.stringify(result), 'utf-8');
    })
    .catch(function (err) {
      res.setHeader('Content-Type', 'text/plain');
      res.end('Error: ' + err);
    });
});

module.exports = router;