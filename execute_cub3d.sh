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

if [ ! -f ./cub3d ]; then
    echo -e "${RED}cub3d executable not found. Running make...${NC}"
    make
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error compiling cub3d. Exiting...🚫${NC}"
        exit 1
    fi
    echo -e "${GREEN}cub3d compiled successfully. ✔️${NC}"
fi

# Default to valid if no input or if input is not 'I'
if [[ -z "$MAP_TYPE" || "$MAP_TYPE" = "v" || "$MAP_TYPE" = "V" ]]; then
    MAP_DIR="./assets/maps/valid"
    echo -e "${GREEN}🗺️ Using valid maps.${NC}"
elif [[ "$MAP_TYPE" = "i" || "$MAP_TYPE" = "I" ]]; then
    MAP_DIR="./assets/maps/invalid"
    echo -e "${RED}🚫 Using invalid maps.${NC}"
else
    echo -e "${RED}Invalid choice. Using default (Valid).🗺️${NC}"
    MAP_DIR="./assets/maps"
fi

# Prompt user for execution mode with a single letter and allow default
echo -e "${YELLOW}Run ${CYAN}[R]andom${YELLOW} map or ${CYAN}[A]ll${YELLOW} maps? Press Enter for default (Random):${NC}"
read -n 1 EXECUTION_MODE
echo

MAP_COUNT=0
MAP_SUCCESS=0
MAP_FAILURE=0

MAPS_FAILED=""

# Default to random if no input or if input is not 'A'
if [[ -z "$EXECUTION_MODE" || "$EXECUTION_MODE" = "r" || "$EXECUTION_MODE" = "R" ]]; then
    # Find a random .cub file from the chosen directory
    MAPFILE=$(find "$MAP_DIR" -type f -name '*.cub' | sort -R | head -n 1)
    if [ -z "$MAPFILE" ]; then
        echo -e "${RED}No .cub files found in $MAP_DIR.🚫${NC}"
        exit 1
    fi
    echo -e "\n-------------------\n\n${GREEN}Running cub3d with random map: ${MAPFILE} 🎲${NC}"
    ./cub3d "$MAPFILE"
elif [[ "$EXECUTION_MODE" = "a" || "$EXECUTION_MODE" = "A" ]]; then
    # Loop through each .cub file in the directory
    for MAPFILE in "$MAP_DIR"/*.cub; do
        if [ -f "$MAPFILE" ]; then
            echo -e "\n-------------------\n\n${GREEN}Running cub3d with map: $MAPFILE 🗺️${NC}"
            ./cub3d "$MAPFILE"
            EXIT_CODE=$?
            wait $!
            if ([ "$MAP_TYPE" = "i" ] || [ "$MAP_TYPE" = "I" ]); then
                if [ $EXIT_CODE -eq 0 ]; then
                    echo -e "${RED}FAILURE: Finished running with map: $MAPFILE ❌${NC}"
                    MAP_FAILURE=$((MAP_FAILURE + 1))
                    MAPS_FAILED+="$MAPFILE\n"
                else
                    echo -e "${GREEN}SUCCESS: Error running with map: $MAPFILE ✔️${NC}"
                    MAP_SUCCESS=$((MAP_SUCCESS + 1))
                fi
            else
                if [ $EXIT_CODE -eq 0 ]; then
                    echo -e "${GREEN}SUCCESS: Finished running with map: $MAPFILE ✔️${NC}"
                    MAP_FAILURE=$((MAP_FAILURE + 1))
                else
                    echo -e "${RED}FAILURE: Error running with map: $MAPFILE ❌${NC}"
                    MAP_SUCCESS=$((MAP_SUCCESS + 1))
                    MAPS_FAILED+="$MAPFILE\n"
                fi
            fi
            MAP_COUNT=$((MAP_COUNT + 1))
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
    echo -e "\n-------------------\n\n${GREEN}Running cub3d with random map: $MAPFILE 🎲${NC}"
    ./cub3d "$MAPFILE"
fi

if [ $MAP_COUNT -gt 1 ] && ([ "$MAP_TYPE" = "i" ] || [ "$MAP_TYPE" = "I" ]); then
    echo -e "\n\n${GREEN}Maps executed: $MAP_COUNT\nMaps passed: $MAP_SUCCESS\n${RED}Maps failed: $MAP_FAILURE${NC}\n"
else
    echo -e "\n\n${CYAN}Maps executed: $MAP_COUNT\n${GREEN}Maps passed: $MAP_FAILURE\n${RED}Maps failed: $MAP_SUCCESS${NC}\n"
fi

if [ $MAP_FAILURE -gt 0 ]; then
    echo -e "${RED}Maps failed:${NC}\n$MAPS_FAILED"
fi

echo -e "${GREEN}\nScript execution complete. ✨\n${NC}"
