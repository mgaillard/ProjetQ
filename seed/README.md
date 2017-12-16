Seed
====
Seed the database with images and update the index.

How does it work ?
------------------
To provide the database with images, add entries to the `init.json` file. 

Example of an entry:
```json
{
    "dct_hash": {"$numberLong" : "8969150024123326104"},
    "url":"https://www.domain.com/image.jpg",
    "indexed":true,
    "active": true
}
```