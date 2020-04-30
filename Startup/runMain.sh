#!/bin/sh

taskset -c 8-11 ./Main.sh -f ../Configurations/sample.cfg -l RealTimeLoader -m StateMachine:Start

