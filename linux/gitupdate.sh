#!/bin/bash
git add *
git commit -m "$1"

set timeout 30
spawn git push
expect "com':"
send "Sherlock-Xujianguo"
expect "com':"
send "Xuchaoran123"

