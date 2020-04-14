# How to install

Install instructions was made for Ubuntu linux 18.04, but you can adopt it to any other *nix system easily.
Tested on:
- Ubuntu 18.04 x64

## Prerequisites:

### Install  curl, jsoncpp, openssl:
```
sudo  apt-get  install  libssl-dev  libcurl4-openssl-dev  libjsoncpp-dev
```

### Install  newest  cmake
Currently it's 3.17
```
sudo  apt-get purge cmake
mkdir  ~/temp
cd  ~/temp
wget  https://github.com/Kitware/CMake/releases/download/v3.17.0/cmake-3.17.0.tar.gz
tar  -xzvf  cmake-3.17.0.tar.gz
cd  cmake-3.17.0/
./bootstrap
make
sudo  make  install
```
Check your version: `cmake  --version`

### Get needed submodules for project:
```
git  submodule  init
git  submodule  update
```

After install, you should [configure](/terminalbot/configure) your bot, and compile.
