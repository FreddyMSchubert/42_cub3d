#!/bin/bash

MAP_DIR="assets/maps/campaign"

for map_file in "$MAP_DIR"/*; do
    ./cub3d "$map_file"
done
