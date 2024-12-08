# Snake Game Project

## Overview

This project is a text-based snake game implemented in C, developed as part of a university assignment. The game combines classic snake gameplay with some additional mechanics, such as collecting coins, avoiding obstacles, and interacting with maze walls and power-ups.

## Features

- **Customizable Maze**: Players can input their own maze designs or use a pre-fabricated maze.
- **Power-ups**:
  - `$`: Adds coins and extends the snake.
  - `T`: Allows the snake to temporarily pass through walls.
  - `!`: Halves the player's coins.
- **Gameplay Mechanics**:
  - Move the snake using `W`, `A`, `S`, `D`.
  - Avoid hitting walls (`#`) or the snake's tail.
  - Collect coins to increase your score.
  - Complete the maze by reaching the endpoint (`x` or `_`).
- **Customizable Levels**: The maze size and object distribution can be tailored by the player.

## Game Rules

1. Use the following keys to move:
   - `W`: Move up
   - `A`: Move left
   - `S`: Move down
   - `D`: Move right
2. Avoid hitting walls (`#`) unless you have collected a `T`.
3. Collect coins (`$`) to earn 10 points each and grow your snake.
4. Touching a `!` halves your coins and reduces the snake's length.
5. Reaching the endpoint (`x` or `_`) completes the game.

## How to Play

1. Compile the game using a C compiler:
   ```bash
   gcc -o snake_game kevin.c
