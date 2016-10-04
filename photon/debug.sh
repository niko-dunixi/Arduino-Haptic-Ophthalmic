#!/usr/bin/env bash

while [ true ]; do
  particle serial monitor | tee debug.log
  echo "Serial connection down, restarting in 5s"
  sleep 5s
done
