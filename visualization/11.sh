#!/bin/sh

printf 'Press e to start simulation'

tcc -DSDL_DISABLE_IMMINTRIN_H -lSDL2 -lSDL2_ttf 11.c -run < ../11.in
