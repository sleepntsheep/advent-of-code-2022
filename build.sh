#!/bin/sh

clean() {
    rm *.bin
}

check_input() {
    if ! [ -f "$i.in" ]
    then
        printf "Day $i: Input file not existing."
        return 1
    fi
    return 0
}

if [ "$1" = "clean" ]
then
    clean
    exit
fi

tput bold
tput setaf 6
printf "C\n"
tput sgr 0

for i in $(seq 25)
do
    [ -f "$i.c" ] || continue
    check_input "$i" || continue
    cc "$i.c" -o "$i.bin" || continue

    printf "Day $i: "
    tput setaf 3
    "./$i.bin" < "$i.in"
    tput sgr 0

    printf "\n"
done
clean

tput bold
tput setaf 6
printf "\nLua\n"
tput sgr 0

for i in $(seq 25)
do
    [ -f "$i.lua" ] || continue
    check_input "$i" || continue

    printf "Day $i: "
    tput setaf 3
    lua "$i.lua" < "$i.in"
    tput sgr 0
done

