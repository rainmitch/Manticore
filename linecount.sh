#!/bin/bash

recurse() {
 for i in "$1"/*;do
    if [ -d "$i" ];then
        recurse "$i"
    elif [ -f "$i" ]; then
        echo "$i"
    fi
 done
}

recurse src/ | xargs cat | wc -l
