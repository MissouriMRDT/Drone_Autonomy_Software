FROM ubuntu:jammy

WORKDIR /app
COPY . .d

RUN apt update && apt install -y build-essential gdb wget

RUN apt install --no-install-recommends -y \
    gcc-10 g++-10 && \