#!/bin/bash
who | cat -n | cut -f 1 | tr -d " "
