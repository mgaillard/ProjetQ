# HamingIndex
Hash image by url
Search for the k nearest neighbors of a hash
Search for the neighbors within a radius of a hash

## Configuration
Each entry in the database should have this schema:

```json
{
    "_id" : ObjectId("..."),
    "dct_hash" : NumberLong(0),
    "url" : "https://www.domain.com/image.jpg",
    "indexed" : true,
    "active": true
}
```

## Dependences
- CMake
- NodeCpp
- OpenCV
- libcurl
- mongocxx

```bash
# Install CMake
$ sudo apt install cmake 

# Install libcurl (OpenSSL version)
$ sudo apt install curl libcurl4-openssl-dev

# Install OpenCV
$ sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev unzip
$ wget -O opencv.zip https://github.com/opencv/opencv/archive/3.2.0.zip
$ unzip opencv.zip
$ cd opencv-3.2.0
$ mkdir build && cd build
$ cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
$ make -j8
$ sudo make install
$ cd ../..

# Install mongocxx
$ sudo apt-get install pkg-config libssl-dev libsasl2-dev
$ wget https://github.com/mongodb/mongo-c-driver/releases/download/1.6.3/mongo-c-driver-1.6.3.tar.gz
$ tar xzf mongo-c-driver-1.6.3.tar.gz
$ cd mongo-c-driver-1.6.3
$ ./configure --disable-automatic-init-and-cleanup
$ make -j8
$ sudo make install
$ cd ..
$ curl -OL https://github.com/mongodb/mongo-cxx-driver/archive/r3.1.1.tar.gz
$ tar -xzf r3.1.1.tar.gz
$ cd mongo-cxx-driver-r3.1.1/build
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..
$ make -j8 && sudo make install
$ cd ../..

# Install NodeCpp
$ sudo apt install libfcgi-dev spawn-fcgi nginx
$ git clone https://github.com/th1337/NodeCpp.git
$ cd NodeCpp
$ git checkout proto
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make -j8
$ cd ..
```

## Build
```bash
$ mkdir build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../src
$ make
```

## Execution
```bash
$ nginx -c <path to nginx.conf>
$ spawn-fcgi -p 8000 -n main
```