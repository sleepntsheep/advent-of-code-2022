#!/bin/sh

if [ "$1" = "clean" ]
then
    rm *.bin
    exit
fi

day_exists() {
    for j in 1 2
    do
        [ -f "${1}_${j}.c" ] && return 0
    done
    return 1
}

compile_day() {
    for j in 1 2
    do
        pref="${1}_${j}"
        src="$pref.c"
        bin="$pref.bin"
        [ -f "$src" ] && cc "$src" -o "$bin"
    done
}

run_day() {
    tput bold
    printf "Day: $i\n"
    tput sgr 0

    in="${1}.in"

    if ! [ -f "$in" ]
    then
        printf "Input file not existing."
        continue
    fi

    for j in 1 2
    do
        bin="${1}_${j}.bin"
        [ -f "$bin" ] || continue
        printf "\t$j: "
        tput setaf 3
        cat "$in" | "./${bin}"
        tput sgr 0
        printf "\n"
    done
}

for i in $(seq 25)
do
    day_exists "$i" || continue
    compile_day "$i"
    run_day "$i"
done


