if ! [ -e textmode-lifestyle ]; then
	echo "No executable found. Preparing to build..."; sleep .6
	echo -n "Checking gcc..."; sleep .4
	if ! [ -e /usr/bin/gcc ]; then
		echo -e "failed!\n\nMake sure gcc is installed.\n"
		exit 1
	fi
	echo "success!"; sleep .4

	echo -n "Checking curses..."; sleep .4
	if ! [ -e /usr/include/curses.h ]; then
		echo -e "failed!\n\ncurses.h not found. Make sure curses (most often ncurses) is installed.\n"
		exit 1
	fi
	echo "success!"; sleep .4
	
	echo -n "Checking mikmod dev..."; sleep .4
	if ! [ -e /usr/include/mikmod.h ]; then
		echo -e "failed!\n\nmikmod.h not found. Make sure mikmod dev package is installed.\n"
		exit 1
	fi
	echo "success!"; sleep .4
	
	echo -n "Checking mikmod..."; sleep .4
	if [[ ! -n $(find /usr/lib* -name 'libmikmod.so*') ]]; then
		echo -e "failed!\n\nMikmod modules not found. Make sure mikmod is installed.\n"
		exit 1
	fi
	echo "success!"; sleep .4
	
    echo "Proceeding to build executable..."; sleep .6

	echo 'Building...'
	gcc -Wall -c main.c &&
	gcc -Wall -c loop.c &&
	gcc -Wall -c bouncer.c &&
	gcc -Wall -c scroller.c &&
	gcc -Wall -c dotbar.c &&
	gcc -Wall -c banner.c &&
	gcc -Wall -c tune.c &&
	gcc -o textmode-lifestyle main.o loop.o bouncer.o scroller.o dotbar.o banner.o tune.o -lncurses -ltinfo -lmikmod -lpthread &&

	if [ $? -eq 0 ]; then
		echo "Build successful. Starting executable..."; sleep 1
		./textmode-lifestyle
	else
		echo "Build failed. Unable to start."
	fi
	
else
	echo -e "\nExecutable found. Starting..."; sleep 1
	./textmode-lifestyle
fi



