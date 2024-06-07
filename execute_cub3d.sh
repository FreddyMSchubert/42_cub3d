#!/bin/bash

# ANSI Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[1;34m'
NC='\033[0m' # No Color

# Prompt user for map type with a single letter and allow default
echo -e "${YELLOW}Select map type: ${CYAN}[V]alid${YELLOW} or ${CYAN}[I]nvalid${YELLOW}? Press Enter for default (Valid):${NC}"
read -n 1 MAP_TYPE
echo

# Default to valid if no input or if input is not 'I'
if [[ -z "$MAP_TYPE" || "$MAP_TYPE" = "v" || "$MAP_TYPE" = "V" ]]; then
    MAP_DIR="./assets/maps"
    echo -e "${GREEN}🗺️ Using valid maps.${NC}"
elif [[ "$MAP_TYPE" = "i" || "$MAP_TYPE" = "I" ]]; then
    MAP_DIR="./assets/invalid_maps"
    echo -e "${RED}🚫 Using invalid maps.${NC}"
else
    echo -e "${RED}Invalid choice. Using default (Valid).🗺️${NC}"
    MAP_DIR="./assets/maps"
fi

# Prompt user for execution mode with a single letter and allow default
echo -e "${YELLOW}Run ${CYAN}[R]andom${YELLOW} map or ${CYAN}[A]ll${YELLOW} maps? Press Enter for default (Random):${NC}"
read -n 1 EXECUTION_MODE
echo

# Default to random if no input or if input is not 'A'
if [[ -z "$EXECUTION_MODE" || "$EXECUTION_MODE" = "r" || "$EXECUTION_MODE" = "R" ]]; then
    # Find a random .cub file from the chosen directory
    MAPFILE=$(find "$MAP_DIR" -type f -name '*.cub' | sort -R | head -n 1)
    if [ -z "$MAPFILE" ]; then
        echo -e "${RED}No .cub files found in $MAP_DIR.🚫${NC}"
        exit 1
    fi
    echo -e "${GREEN}Running cub3d with random map: ${MAPFILE} 🎲${NC}"
    ./cub3d "$MAPFILE"
elif [[ "$EXECUTION_MODE" = "a" || "$EXECUTION_MODE" = "A" ]]; then
    # Loop through each .cub file in the directory
    for MAPFILE in "$MAP_DIR"/*.cub; do
        if [ -f "$MAPFILE" ]; then
            echo -e "${GREEN}Running cub3d with map: $MAPFILE 🗺️${NC}"
            ./cub3d "$MAPFILE"
            wait $!
            echo -e "${GREEN}Finished running with map: $MAPFILE ✔️${NC}"
        else
            echo -e "${RED}No .cub files found in $MAP_DIR.🚫${NC}"
            break
        fi
    done
else
    echo -e "${RED}Invalid choice. Using default (Random). 🎲${NC}"
    MAPFILE=$(find "$MAP_DIR" -type f -name '*.cub' | sort -R | head -n 1)
    if [ -z "$MAPFILE" ]; then
        echo -e "${RED}No .cub files found in $MAP_DIR.🚫${NC}"
        exit 1
    fi
    echo -e "${GREEN}Running cub3d with random map: $MAPFILE 🎲${NC}"
    ./cub3d "$MAPFILE"
fi

echo -e "${GREEN}Script execution complete. ✨${NC}"
