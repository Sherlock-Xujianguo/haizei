#!/bin/bash
a=`echo "1 2 3 4 5 6 7 9 a v 你好 . /8" | tr -c -d [0-9" "] | tr -s " " " " | tr " " "+"`
rst=$((a))
echo $rst

