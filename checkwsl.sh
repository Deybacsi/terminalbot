#!/bin/bash

# check to see if it's native linux or running inside windows subsystem for linux

set -e
if grep -qEi "(Microsoft|WSL)" /proc/version &> /dev/null ; then
    echo "Windows 10 Bash"
else
    echo "Anything else"
fi
