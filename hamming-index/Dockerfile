FROM ubuntu:latest
LABEL maintainer="Mathieu GAILLARD"

# Install dependences
RUN apt update && \
    apt install -y build-essential cmake curl git libavcodec-dev libavformat-dev \ 
                   libcurl4-openssl-dev libdc1394-22-dev libfcgi-dev libgtk2.0-dev \
                   libjasper-dev libjpeg-dev libpng-dev libsasl2-dev libssl-dev libswscale-dev \
                   libtbb-dev libtbb2 libtiff-dev nginx pkg-config python-dev python-numpy spawn-fcgi unzip wget && \
    apt clean

# Install OpenCV
RUN mkdir /tmp/OpenCV && cd /tmp/OpenCV && \
    wget -O opencv.zip https://github.com/opencv/opencv/archive/3.2.0.zip && \
    unzip opencv.zip && cd opencv-3.2.0 && \
    mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j8 && make install && ldconfig && \
    cd ../.. && rm -rf OpenCV

# Install MongoCxx
RUN mkdir /tmp/mongocxx && cd /tmp/mongocxx && \
    wget https://github.com/mongodb/mongo-c-driver/releases/download/1.6.3/mongo-c-driver-1.6.3.tar.gz && \
    tar xzf mongo-c-driver-1.6.3.tar.gz && cd mongo-c-driver-1.6.3 && \
    ./configure --disable-automatic-init-and-cleanup && \
    make -j8 && make install && cd .. && \
    curl -OL https://github.com/mongodb/mongo-cxx-driver/archive/r3.1.1.tar.gz && \
    tar -xzf r3.1.1.tar.gz && cd mongo-cxx-driver-r3.1.1/build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j8 && make install && \
    cd ../../.. && rm -rf mongocxx

# Install NodeCpp
RUN cd /root && \
    git clone https://github.com/th1337/NodeCpp.git && cd NodeCpp && \
    git checkout proto && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8 && \
    cd ..

COPY ./src /root/HammingIndex

# Build HammingIndex
RUN cd /root/HammingIndex && mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8

WORKDIR /root/HammingIndex/build

CMD ["spawn-fcgi", "-p", "8000", "-n", "main"]