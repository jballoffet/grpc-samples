FROM ubuntu:18.04

# Setup environment
ENV DEBIAN_FRONTEND noninteractive

# Install development packages
RUN apt-get update && apt-get install -y \
  sudo \
  git \
  mercurial \
  build-essential \
  vim \
  openssh-server \
  software-properties-common \
  bash-completion \
  debian-keyring \
  debian-archive-keyring \
  curl \
  cmake \
  python3 \
  tmux \
  autoconf \
  libtool \
  pkg-config

# Install Bazel
RUN echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
  && curl https://bazel.build/bazel-release.pub.gpg | apt-key add -
RUN apt-get update && apt-get install -y bazel

# Set up workspace
RUN mkdir /workspace
WORKDIR /workspace
CMD tmux
