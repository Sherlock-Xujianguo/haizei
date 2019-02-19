#!/bin/bash
rec=`ls`
for each_name in $rec;do
    flag=0
    for i in `seq 0 9`;do
        filename="$i.txt"
        flag=($flag+1)
        if (($flag==1));then
            touch "$filename"
        fi
        echo $each_name >> "$filename"
        if (($flag==10));then
            flag=0
            break
        fi
    done
done
