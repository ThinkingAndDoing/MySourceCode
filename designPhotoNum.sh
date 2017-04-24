#!/bin/sh
jpglst=`find . -name *.jpg`
pnglst=`find . -name *.png`
giflst=`find . -name *.gif`
bmplst=`find . -name *.bmp`
loop=1
for file in $jpglst
do
mv $file $loop.jpg
loop=`expr $loop + 1`
done
loop=1
for file in $pnglst
do
mv $file $loop.png
loop=`expr $loop + 1`
done
loop=1
for file in $giflst
do
mv $file $loop.gif
loop=`expr $loop + 1`
done
loop=1
for file in $bmplst
do
mv $file $loop.bmp
loop=`expr $loop + 1`
done
loop=1

