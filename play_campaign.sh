#!/bin/bash

MAP_DIR="assets/maps/campaign"

# Accept a skip parameter
SKIP=${1:-0}
COUNTER=0

rm -f "save.cubsave"

for map_file in "$MAP_DIR"/*; do
	if [ $COUNTER -lt $SKIP ]; then
		((COUNTER++))
		continue
	fi

	while true; do
		./cub3d "$map_file"
		exit_code=$?

		if [[ $exit_code -eq 0 ]]; then
			break
		elif [[ $exit_code -eq 214 ]]; then
			exit
		fi
	done

	((COUNTER++))
done

echo "Campaign completed!"
echo "But I'm already bored..."
echo "Wait, what's that over there?"
echo "Infinite random gen arcade mode, here I come!"

while true; do
	./cub3d
done
