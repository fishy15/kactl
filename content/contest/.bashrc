run () {
	ok=1
	if [[ ! -f $1 || $1 -ot $1.cpp ]]
	then
		g++ -Wall -std=c++17 $1.cpp -O2 -o $1 -Wall -std=c++17 -Wextra -Wshadow || ok=0
	fi
	[[ $ok -eq 1 ]] && ./$1
}

xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'
