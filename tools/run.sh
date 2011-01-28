#!/bin/bash

echo Building assets
rm cache.sdl.txt 2> /dev/null
rm StringCache.txt 2> /dev/null
./sexporter -i assets.xml -p sdl -v
cp assets.h ../assets.h
