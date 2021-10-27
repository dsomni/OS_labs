J=./lofsdisk
echo "Dmitry" > $J/file1
echo "Beresnev" > $J/file2

mkdir -p $J/{bin,lib64,lib}
mkdir -p $J/lib/x86_64-linux-gnu
cp -v /bin/{bash,ls} $J/bin

list="$(ldd /bin/bash | egrep -o '/lib.*\.[0-9]')"
for i in $list; do cp  -v "$i" "${J}${i}"; done

gcc ./ex2.c -o ./ex2
sudo ./ex2 1 > ./ex2.txt
sudo ./ex2 0 >> ./ex2.txt