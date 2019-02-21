#!/bin/bash
time_info="`date +%F`__`date +%T`"
last_info=`last | awk 'BEGIN{} {if($2!="system"&&$2!=":0"&&NF==10){printf("%s\n",$0)}} END{}'`
user_list=`last | awk 'BEGIN{} {if($2!="system"&&$2!=":0"&&NF==10){printf("%s\n",$0)}} END{}' | cut -d " " -f 1 | uniq`
user_num=`echo ${#user_list[*]}`
active_user=`count=0;for each in $user_list;do if ((count==3));then break; fi; let count++; echo $each; done`
active_user="`echo $active_user | tr " " "," `"
rooter=`last | awk 'BEGIN{} {if($2==":0"){printf("%s\n",$0)}} END{}' | cut -d " " -f 1 | uniq`
logged_in=`last | awk 'BEGIN{} {if($9=="logged"&&$10=="in"&&$2~/pts/){printf("%s_%s_%s\n", $1, $3, $2)}} END{}' | cut -d " " -f 1 | uniq | tr " " ","`


echo "$time_info $user_num [$active_user] [$rooter] [$logged_in]"

