#!/bin/sh
cpplst=`find . -name *.cpp`
clst=`find . -name *.c`
prolst=`find . -name *.pro`
hlst=`find . -name *.h`
for file in $cpplst
do
mv $file $file.txt
done
for file in $clst
do
mv $file $file.txt
done
for file in $prolst
do
mv $file $file.txt
done
for file in $hlst
do
mv $file $file.txt
done
