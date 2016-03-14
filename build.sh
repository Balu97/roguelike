#!/bin/bash
gcc main.c entitys.c -o roguelike.out -lncurses && cat buildnumber.h | awk -F"\"" ' { OFS="\"" } /#define/ { print $1,$2+1,$3; } !/#define/ { print $0 } ' > buildnumbertmp.h && mv buildnumbertmp.h buildnumber.h
