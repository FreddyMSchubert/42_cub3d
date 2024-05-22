#!/bin/bash

# random file from assets/maps
MAPFILE=$(find ./assets/maps -type f | sort -R | head -n 1)

echo "Running cub3d with map: $MAPFILE"

./cub3d "$MAPFILE"
