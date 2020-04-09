#!/bin/bash
export CMAKE_C_COMPILER=/usr/bin/gcc
cmake --build . --target clean
make

echo "run ./terminalbot to run the bot"
