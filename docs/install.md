# How to install

Below instructions were made for Ubuntu linux 18.04, but you can adopt it to any other *nix system easily.

Tested on:
- Ubuntu 18.04 x64
- Raspberry Pi 3B+, Raspbian Buster 32bit
- Windows 10, Windows subsystem for Linux with Ubuntu 20.04

# Installing on Windows 10

---

You will need to enable the inbuilt linux subsystem feature in Control Panel/Programs and features:
![enable-wsl](images/wsl.png)

After reboot go to MS Store, and install Ubuntu:
![download-ubuntu](images/wsl-ubuntu.png)

Select a linux user name, and a password:
![setup-ubuntu](images/wsl-userpw.png)
This username is your username inside the linux install. Your selected password is usually referred to as **root** or **sudo** password. You will be asked for this every time when you install something inside your linux subsystem.

Now you have a working linux command line. Copy/paste the below commands to the window:
```
sudo apt-get update
sudo apt-get install libssl-dev libcurl4-openssl-dev libjsoncpp-dev git cmake build-essential
```

You can continue with the steps in the linux install section. (You can skip the first 2 apt-get commands, because we already did it above ;)

# Installing on Windows 8 and below

---

You can install linux on a virtual machine, check [this video](https://www.youtube.com/watch?v=QbmRXJJKsvs) for details.

# Installing on linux

---

Grab a terminal, and run these magical commands.

### Install  curl, jsoncpp, openssl, git:
```
sudo apt-get update
sudo apt-get install libssl-dev libcurl4-openssl-dev libjsoncpp-dev git
```

### Install  newest  cmake:
This section is optional, if you get errors during the compilation of the bot, try to install the newest cmake. As I remember I had some issues with an earlier version on Uubuntu 18.04.

Currently we will install v3.17:
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
It will take some time, get a coffee and relax ;)
Finally, check your version: `cmake --version`

### Clone terminalbot to your computer

```
git clone https://github.com/Deybacsi/terminalbot.git
cd terminalbot
git submodule init
git submodule update
```


Now you should [configure](/terminalbot/configure) your bot, and compile.
