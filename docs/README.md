**This project is currenty in a *proof-of-concept* state to test Binance API and its features.
Just to see / try if it's possible to make some bucks for cofee (or beer ;).**
**This software is untested, and are under development. Unpredictable and unhandled behaviours can happen.**

**DO NOT USE it for your daily trading! You can loose your money if something goes wrong!**

**You have been warned.**

# TerminalBot


Simple C++ trading bot using the 7, 25, 99 moving average (MA) indicators to trade cryptocurrencies on exchanges.

## How to install

Install instructions was made for Ubuntu 18.04, but you can adopt it to any other *nix system easily.
Tested on:
- Ubuntu 18.04

### Prerequisites:

#### Install  curl, jsoncpp, openssl:
`sudo  apt-get  install  libssl-dev  libcurl4-openssl-dev  libjsoncpp-dev`

#### Install  newest  cmake
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

#### Get needed submodules for project:
```
git  submodule  init
git  submodule  update
```
#### Build  bot:
```
cmake .
make
```

Or you can run `./compile.sh` to get submodules, and build the source.

### Run:

`./terminalbot` :)

## Configuration
Currently configuration options are only available in the form of direct source code modification. This means, after configuring your bot, you'll need to recompile.

Please see
