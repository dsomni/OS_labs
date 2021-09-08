./ex2 &
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14
do
    pstree | grep ex2
    sleep 2
    echo "\n\n"
done