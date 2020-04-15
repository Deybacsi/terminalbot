# How to install

Below instructions were made for Ubuntu linux 18.04, but you can adopt it to any other *nix system easily.

Tested on:
- Ubuntu 18.04 x64

## Prerequisites:

### Install  curl, jsoncpp, openssl, git:
```
sudo apt-get install libssl-dev libcurl4-openssl-dev libjsoncpp-dev git
```

### Install  newest  cmake:
Currently it's 3.17
```
sudo apt-get purge cmake
mkdir ~/temp
cd ~/temp
wget https://github.com/Kitware/CMake/releases/download/v3.17.0/cmake-3.17.0.tar.gz
tar -xzvf cmake-3.17.0.tar.gz
cd cmake-3.17.0/
./bootstrap
make
sudo make install
```
Check your version: `cmake --version`

### Clone terminalbot to your computer

```
git clone https://github.com/Deybacsi/terminalbot.git
cd terminalbot
git submodule init
git submodule update
```


Now you should [configure](/terminalbot/configure) your bot, and compile.
