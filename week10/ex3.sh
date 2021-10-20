echo "Hello, world!" > _ex3.txt
chmod a-x _ex3.txt
ls -l _ex3.txt > ex3.txt
chmod uo+rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod uo+rwx _ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g=u _ex3.txt
ls -l _ex3.txt >> ex3.txt
echo "660 - User and Group can only Read and Write; Others can do nothing" >> ex3.txt
echo "775 - User and Group can do everything; Others can only Read and Execute" >> ex3.txt
echo "777 - Everyone can do everything" >> ex3.txt