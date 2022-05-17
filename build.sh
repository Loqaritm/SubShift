#!/bin/bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
g++ -std=c++11 -I $SCRIPT_DIR/include $SCRIPT_DIR/source/main.cpp -o "$PWD"/subshift
