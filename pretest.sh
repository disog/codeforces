#!/usr/bin/sh
build/debug/contest/$1/$1_$2 | diff - contest/$1/$2/output
