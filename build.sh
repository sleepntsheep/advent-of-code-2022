for f in *.c
do
    cc "$f" -o "$f.bin"
done

