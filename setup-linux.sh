#!/usr/bin/env bash
set -e

sudo adduser $USER vboxsf #For mounting vbox folders
sudo apt-get update
sudo apt-get install arduino arduino-core
sudo usermod -aG dialout $USER #Enable USB port for arduino
sudo reboot
