#!/usr/bin/env bash

while [ true ]; do
  particle serial monitor | tee debug.log
  echo "Serial connection down, restarting in 1s"
  sleep 1s
done
