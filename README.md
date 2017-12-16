Projet Q
========
This software is a reverse image search engine.

Authors
-------
We are two French engineers.

Mathieu Gaillard - Guillaume Kheng

How does it work ?
------------------
The system is based on a DCT perceptual hash function that maps images onto 64 bits binary codes. A Hamming distance is used to compare two binary codes.

To provide the database with images, add images to `data/init/init.json`

Run
---
```bash
# Run the application
$ docker-compose up 
```

License
-------
See the LICENSE file.
