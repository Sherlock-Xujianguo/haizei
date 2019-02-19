#!/bin/bash
last | cut -d " " -f 1 | grep -v wtmp | grep -v '^$' | sort | uniq -c | sort -n -t " " -k 1
