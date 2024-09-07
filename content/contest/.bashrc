run () {
	ok=1
	if [[ ! -f $1 || $1 -ot $1.cpp ]]
	then
		g++ $1.cpp -O2 -o $1 -std=c++17 -Wall -Wextra -Wshadow -Wconversion -fsanitize=undefined,address || ok=0
	fi
	[[ $ok -eq 1 ]] && ./$1
}

xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'
