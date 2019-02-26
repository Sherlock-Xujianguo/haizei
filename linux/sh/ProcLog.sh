#!/bin/bash
eval $(ps -aux --sort=-%cpu -h | awk -v num=0 \
    '{if($3 < 50) {exit} else {num++;printf("cpuproid["num"]=%d;",$2);} } END {printf("cpunum=%d;",num)}')
eval $(ps -aux --sort=-%mem -h | awk -v num=0 \
    '{if($4 < 50) {exit} else {num++;printf("memproid["num"]=%d;",$2);} } END {printf("memnum=%d;",num)}')

if [[ $cpunum -gt 0 ]];then
    echo $cpunum
    sleep 3
    else
        exit 0
fi

time_info=`date +"%F__%T"`

if [[ $cpunum -gt 0 ]];then
    count=0
    for i in ${cpuproid[*]};do
        echo $i
        count=$[ $count + 1 ]
        eval $(ps -aux -q $i -h | awk -v num=$count \
            '{if($3 < 50){exit} else {printf("cpuproname["num"]=%s;\
            cpupropid["num"]=%s;cpuname["num"]=%s;\
            cpuprocpu["num"]=%2.2f;cpupromem["num"]=%2.2f;",$11,\
            $2,$1,$3,$4)};} END{printf("cpuchecknum=%d",num)}')
    done
fi


if [[ $memnum -gt 0 ]];then
    count=0
    for i in ${memproid[*]};do
        echo $i
        count=$[ $count + 1 ]
        eval $(ps -aux -q $i -h | awk -v num=$count \
            '{if($3 < 50){exit} else {printf("memproname["num"]=%s;\
            mempropid["num"]=%s;memname["num"]=%s;\
            memprocpu["num"]=%2.2f;mempromem["num"]=%2.2f;",$11,\
            $2,$1,$3,$4);}} END{printf("memchecknum=%d",num)}')
    done
fi

if [[ $cpuchecknum -gt 0 ]];then
    count=0
    for i in ${cpuproname[*]};do
        count=$[ $count + 1 ]
        echo "$time_info ${cpuproname["count"]} ${cpupropid["count"]} ${cpuname["count"]} ${cpuprocpu["count"]} ${cpupromem["count"]}"
    done
fi


if [[ $memchecknum -gt 0 ]];then
    count=0
    for i in ${memproname[*]};do
        count=$[ $count + 1 ]
        echo "$time_info ${memproname["count"]} ${mempropid["count"]} ${memname["count"]} ${memprocpu["count"]} ${mempromem["count"]}"
    done
fi
    
    
    
    
    
