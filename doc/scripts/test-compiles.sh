mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ build/temp.cpp -c -O2 -std=c++17 -Wall -Wextra -Werror -Wshadow -Wconversion && rm temp.o build/temp.cpp
