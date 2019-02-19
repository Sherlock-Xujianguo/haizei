#!/bin/bash
cat /etc/passwd | head -20 | tail -11 | cut -d ":" -f 1,3,4,5
