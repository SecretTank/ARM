#!/bin/sh
#current_d = `pwd`
#cd ../Binary
#if [ $? = 1 ]
#then
#	cd ..
#	mkdir Binary
#	cd Binary
#fi
/usr/share/Qt5.2.1/5.2.1/gcc_64/bin/qmake -o Makefile Tremor.pro > /dev/null
make -s
if [ $? = 0 ]
then
	./Tremor &
else
	echo "you got an error"
fi
