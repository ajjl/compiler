#!/bin/bash

arg=$1

as -o ${arg}.o ${arg}
gcc -o ${arg}.bin ${arg}.o
