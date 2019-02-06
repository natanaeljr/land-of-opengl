FROM ubuntu:latest
#FROM thewtex/opengl:latest

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
    git \
    g++ \
    cmake \
    libx11-dev \
    libxrandr-dev \
    libxcursor-dev \
    libxinerama-dev \
    libgl1-mesa-dev \
    mesa-common-dev

