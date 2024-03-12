FROM ubuntu:jammy

WORKDIR /opt
COPY . .d

RUN apt update && apt install -y build-essential gdb \
    wget git cmake

#RUN apt install --no-install-recommends -y \
 #   gcc-10 g++-10 && \
    #git clone https://github.com/mavlink/MAVSDK.git && \
    #git submodule update --init --recursive && \
    #cmake -DCMAKE_BUILD_TYPE=Debug -Bbuild/default -H. && \
    #cmake --build build/default -j8 && \ 