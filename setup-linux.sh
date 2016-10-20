#!/usr/bin/env bash
set -e

sudo adduser $USER vboxsf
sudo apt-get update
sudo apt-get install arduino arduino-core
sudo usermod -aG dialout $USER
