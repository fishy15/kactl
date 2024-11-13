set cin aw ai is ts=4 sw=4 tm=50 rnu noeb bg=dark ru cul mouse=a
sy on | no ; :
" Select region and then type :Hash to hash your selection.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
