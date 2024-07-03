#!/bin/bash

MAP_DIR="assets/maps/campaign"

rm -f "save.cubsave"

for map_file in "$MAP_DIR"/*; do
	while true; do
		./cub3d "$map_file"
		exit_code=$?

		if [[ $exit_code -eq 0 ]]; then
			break
		fi
	done
done

while true; do
    ./cub3d
done
