# Botanist Flower Collector Game (C)

This project implements a console-based flower collecting game where the player acts as a botanist exploring a forest, collecting rare flowers. The game uses a 2D map and manages player movement, obstacles, and flower collection.

## Features

- Read initial forest map and botanist location from `init.txt`
- Display forest state and botanist's position
- Move the botanist using keyboard commands (`r`, `l`, `u`, `d`)
- Collect flowers (`X` on the map) until all are found
- Update and print the number of flowers collected and bottles used
- Avoid trees (`T`) and check for invalid moves
- Save the final state to `last.txt` upon game completion

## How to Play

1. Prepare the `init.txt` file in the correct format (forest size, botanist start position, map layout).
2. Compile the code:
    ```bash
    gcc 220104004043.c -o botanist_game
    ```
3. Run the game:
    ```bash
    ./botanist_game
    ```
4. Move the botanist using:
    - `r`: right
    - `l`: left
    - `u`: up
    - `d`: down

5. The game ends when all flowers are collected. The final map and stats are saved to `last.txt`.

## File Descriptions

- `220104004043.c`: Main game source code.
- `init.txt`: Initial map, botanist position, and bottle information (input file, required to start the game).
- `last.txt`: Output file storing the end state after the game ends.

## Example Output (`last.txt`)

