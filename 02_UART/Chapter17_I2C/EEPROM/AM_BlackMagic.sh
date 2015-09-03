#!/bin/bash

echo "1:	Ahmad"
echo "2:	Arvin"
echo "3:	Ehsan"
echo "4:	Mostafa"
echo "5:	Darabi"
echo "6:	Bijan"
echo "7:	Gholi"
echo "8:	Navid"
echo "9:	Taghi"
echo "10:	Vahid"
echo "11:	Master"

while [ 1 ]; do
	printf ">"
	read COMMAND
	cd ../../..
	if [ $COMMAND = "1" ]; then
		BRANCH=Ahmad
		ACK=1
    fi
	if [ $COMMAND = "2" ]; then
		BRANCH=Arvin
		ACK=1
    fi
	if [ $COMMAND = "3" ]; then
		BRANCH=Ehsan
		ACK=1
    fi
	if [ $COMMAND = "4" ]; then
		BRANCH=M_A
		ACK=1
    fi
	if [ $COMMAND = "5" ]; then
		BRANCH=ahmaddarabi
		ACK=1
    fi
	if [ $COMMAND = "6" ]; then
		BRANCH=bijan
		ACK=1
    fi
	if [ $COMMAND = "7" ]; then
		BRANCH=gholi
		ACK=1
    fi
	if [ $COMMAND = "8" ]; then
		BRANCH=navid
		ACK=1
    fi
	if [ $COMMAND = "9" ]; then
		BRANCH=taghi
		ACK=1
    fi
	if [ $COMMAND = "10" ]; then
		BRANCH=vahid
		ACK=1
    fi
	if [ $COMMAND = "11" ]; then
		BRANCH=master
		ACK=1
    fi
	if [ $COMMAND = "quit" ]; then
		break
    fi
	if [ $ACK = 1 ]; then
		git checkout $BRANCH
		git pull origin $BRANCH
		cd "./03 - AVR/Chapter17_I2C/EEPROM"
		make
		make flash
	else
		echo "Error:commad incorrect"
    fi
done
