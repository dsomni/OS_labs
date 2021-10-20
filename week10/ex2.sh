FILE="../week1/file.txt"
echo "Hello, world!" > $FILE
INODENUMBER=$(ls -i $FILE | cut -f1 -d " ")
echo $INODENUMBER > ex2.txt
link $FILE _ex2.txt
find . -inum $INODENUMBER >> ex2.txt
find . -inum $INODENUMBER -exec rm {} \; >> ex2.txt