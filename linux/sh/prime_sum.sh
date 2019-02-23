#!/bin/bash
declare -a prime
for i in `seq 1 5000`; do
    let prime[i]=0
done

declare -a sta
counter=0
sum=0
for i in `seq 2 5000`; do
    if [[ ${prime[i]} -eq 0 ]]; then
        let sum+=i
        echo $i
        echo $sum
        let sta[counter]=i
        let counter++
        for (( j=0; j<${#sta[*]}; j++ )); do
            if [[ ${sta[j]}*$i -ge 5000 ]]; then
                continue;
            fi
            let prime[sta[j]*i]=1
        done
        else 
            for (( j=0; j<${#sta[*]}; j++ )); do
                let prime[sta[j]*i]=1
                let k=i%sta[j]
                if [[ $k -eq 0 ]]; then
                    break
                fi
            done
    fi
done
echo $sum
