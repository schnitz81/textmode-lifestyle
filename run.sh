if ! [ -e textmode-lifestyle ]; then
	echo "No executable found. Preparing to build..."; sleep .4
	echo -n "Checking gcc.."; sleep .2
	if [ -z "$(which gcc)" ]; then
		echo -e "failed!\n\nMake sure gcc is installed.\n"
		exit 1
	else
		echo "success!"; sleep .2
	fi

	echo -n "Checking curses..."; sleep .2
	if printf "#include <curses.h>\n" | gcc -E -x c - >/dev/null 2>&1; then
		echo "success!"; sleep .2
	else
		echo -e "failed!\n\ncurses.h header file not found. Make sure curses (most often ncurses) is installed.\n"; exit 1
	fi

	echo -n "Checking mikmod dev..."; sleep .2
	if printf "#include <mikmod.h>\n" | gcc -E -x c - >/dev/null 2>&1; then
		echo "success!"; sleep .2
	else
		echo -e "failed!\n\nmikmod.h header file not found. Make sure mikmod dev package is installed.\n"; exit 1
	fi

	echo -n "Checking mikmod..."; sleep .2
	if ldconfig -p | grep -qE 'libmikmod\.so'; then
		echo "success!"; sleep .2
	else
		echo -e "failed!\n\nMikmod library not found. Make sure mikmod is installed.\n"; exit 1
	fi

    echo "Proceeding to build executable..."; sleep .6

	echo 'Building...'
	gcc -Wall -c main.c &&
	gcc -Wall -c loop.c &&
	gcc -Wall -c bouncer.c &&
	gcc -Wall -c scroller.c &&
	gcc -Wall -c starfield.c &&
	gcc -Wall -c dotbar.c &&
	gcc -Wall -c banner.c &&
	gcc -Wall -c tune.c &&
	gcc -o textmode-lifestyle main.o loop.o bouncer.o scroller.o starfield.o dotbar.o banner.o tune.o -lncurses -ltinfo -lmikmod -lpthread &&

	if [ $? -eq 0 ]; then
		echo "Build successful. Starting executable..."; sleep .6
		./textmode-lifestyle
	else
		echo "Build failed. Unable to start."
	fi

else
	echo -e "\nExecutable found. Starting..."; sleep .4
	./textmode-lifestyle
fi



