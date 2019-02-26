#!/bin/bash
time="`date +%F`__`date +%T`"
meminfo=`free -m | tail -n -2 | head -n 1 | awk 'BEGIN{} {printf("%d %d",$2,$4)} END{}'`
total="`echo $meminfo | cut -d " " -f 1`"
free="`echo $meminfo | cut -d " " -f 2`"
upper=$((total-free))
useper1=$(echo "scale=1;$upper*100/$total"|bc)
useper2=$(echo "scale=1;0.3*$1+0.7*$useper1"|bc)

echo "$time $total"M" $free"M" $useper1"%" $useper2"%
