mkdir -p build
FILE="$1"
echo "
#include \"../content/contest/template.cpp\"
#include \"../$FILE\"
" >build/temp.cpp
g++ build/temp.cpp -O2 -std=c++17 -Wall -Wextra -Wfatal-errors -Wshadow -Wconversion && rm a.out build/temp.cpp
