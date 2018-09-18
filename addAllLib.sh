#!/bin/sh
#$PWDPTH=`pwd`

#export PATH=$PATH:/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/bin
export PATH=/usr/local/bin/:/usr/bin:/bin:$PATH
CUR_PATH=`pwd`
basepath=$(cd `dirname $0`; pwd)
echo $basepath
echo $CUR_PATH


#sudo password

#mysql lib
if [ -f ~/.pws ]; then
	pw=$(cat ~/.pws)
	echo $pw|sudo -S apt-get install libmysql++-dev
else
	sudo apt-get install libmysql++-dev
fi

sudo apt-get install mysql-server mysql-client

#protobuf 2.5.0
# https://github.com/protocolbuffers/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.bz2
if [ -d lib ]; then
	if [ ! -d protobuf-2.5.0 ]; then
		#statements
		cd lib
		wget https://github.com/protocolbuffers/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.bz2
		tar -jxvf protobuf-2.5.0.tar.bz2
	else
		cd protobuf-2.5.0
		./configure
		if [ -f Makefile]; then
			#statements
			make
			sudo make install
			sudo echo '/usr/local/lib' > /etc/ld.so.conf.d/bprotobuf.conf
			sudo ldconfig
		fi
		cd ../..
	fi
else
	mkdir lib
	cd lib
	wget https://github.com/protocolbuffers/protobuf/releases/download/v2.5.0/protobuf-2.5.0.tar.bz2
	tar -jxvf protobuf-2.5.0.tar.bz2
	cd protobuf-2.5.0
	./configure
	if [ -f Makefile]; then
		make
		sudo make install
		sudo echo '/usr/local/lib' > /etc/ld.so.conf.d/bprotobuf.conf
		sudo ldconfig
	fi
	cd ..
fi

#bison tool
sudo apt install bison


#curl lib
sudo apt-get install libcurl4-openssl-dev

#oauth lib
sudo apt-get install liboauth-dev

#ssl lib
sudo apt-get install libssl-dev

#lua protobuf
sudo ln -s ${basepath}/src/ServerEngine/Zone/protoc-gen-lua/plugin/protoc-gen-lua /usr/local/bin/

sudo chmod 777 /usr/local/bin/protoc-gen-lua
