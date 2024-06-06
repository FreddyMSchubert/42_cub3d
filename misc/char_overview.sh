# useful e.g. to verify that there are no unwanted characters in a given maze

cat giant.cub | fold -w1 | sort | uniq -c | awk '{print $2 " - " $1}'