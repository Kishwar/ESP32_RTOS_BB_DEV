#!/usr/bin/env bash

##
 # @file build.sh
 #
 # @brief Build bash script to build using MacOS terminal
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 08/03/2022
 #
 ##

_CLEAN=0
_BUILD=0
_FLASH=0
_MONITOR=0

while getopts "cbfm" flag
do
  case "${flag}" in
    c) _CLEAN=1
      ;;
    b) _BUILD=1
      ;;
    f) _FLASH=1
      ;;
    m) _MONITOR=1
      ;;
  esac
done

cwd=$(pwd)

echo "BUILD: $_BUILD, CLEAN: $_CLEAN, FLASH: $_FLASH, MONITOR: $_MONITOR"


echo "Change to IDF_PATH: ====== $IDF_PATH"
cd $IDF_PATH
echo $(pwd)
. ./export.sh

echo "Change to project directory: ====== $cwd"
cd $cwd

# build
if [[ $_BUILD -eq 1 ]]; then
  if [[ -d src ]]; then
    mv src main
  fi
  python3 $IDF_PATH/tools/idf.py menuconfig
  python3 $IDF_PATH/tools/idf.py build
  if [[ -d main ]]; then
    mv main src
  fi
fi

# clean
if [[ $_CLEAN == 1 ]]; then
  python3 $IDF_PATH/tools/idf.py clean
fi

# flash
if [[ $_FLASH == 1 ]]; then
  python3 $IDF_PATH/tools/idf.py -p /dev/cu.SLAB_USBtoUART flash
fi

# flash + monitor
if [[ $_MONITOR == 1 ]]; then
  python3 $IDF_PATH/tools/idf.py -p /dev/cu.SLAB_USBtoUART flash monitor
fi
