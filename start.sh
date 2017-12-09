#!/bin/bash

cd ~
git clone https://github.com/progrmoiz/progr-maze.git
cd progr-maze
cd src
make all
cd ..
cd build
rm -rf ~/progrmaze
mkdir ~/progrmaze
cp -rf * ~/progrmaze
cd ~
rm -rf progr-maze
cd ~/progrmaze
# running program
./progrmaze
