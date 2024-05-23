FROM mcr.microsoft.com/devcontainers/base:ubuntu

# Update and install all dependencies
RUN apt-get update && apt-get install -y \
    xz-utils \
    gcc \
    clang \
    git-all \
    git-core \
    sudo \
    build-essential \
    cmake \
    valgrind \
    libcppunit-dev \
    curl \
    python3-pip \
    python-dev-is-python3 \
    python3.10-venv \
	libx11-dev \
	libglfw3-dev \
	libglfw3 \
	xorg-dev

RUN apt install -y cppcheck clang-tidy

# Upgrade pip and setuptools, and install norminette
RUN python3 -m pip install --upgrade pip setuptools && \
    python3 -m pip install norminette && \
    python -m pip install matplotlib
