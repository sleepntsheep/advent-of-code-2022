#!/bin/sh

clean() {
    rm *.bin
}

day_exists() {
    [ -f "$1.c" ] && return 0
    return 1
}

compile_day() {
    src="$i.c"
    bin="$i.bin"
    [ -f "$src" ] || continue
    cc "$src" -o "$bin"
}

run_day() {
    tput bold
    printf "Day $i:  "
    tput sgr 0

    in="${1}.in"

    if ! [ -f "$in" ]
    then
        printf "Input file not existing."
        continue
    fi

    bin="$1.bin"
    [ -f "$bin" ] || continue
    tput setaf 3
    "./${bin}" < "$in"
    tput sgr 0
    printf "\n"
}

if [ "$1" = "clean" ]
then
    clean
    exit
fi

for i in $(seq 25)
do
    day_exists "$i" || continue
    compile_day "$i"
    run_day "$i"
done
clean


