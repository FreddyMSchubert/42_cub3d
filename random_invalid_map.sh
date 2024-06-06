#!/bin/bash

MAPFILE=$(find ./assets/invalid_maps -type f -name '*.cub' | sort -R | head -n 1)

echo "Running cub3d with invalid map: $MAPFILE"

./cub3d "$MAPFILE"