# Quarto
## What's Quatro about?
🎲 Quatro is a strategy game played on a 4x4 grid, and the objective is to align 4 pieces with a common attribute:
- color
- shape
- height
- solidity

in a line or in a square. What makes the game interesting is that each player chooses the piece to be used by the next player which allows for additonal strategy and depth.

## Set up
> [!NOTE]
> This project is designed to work on Linux based distributions - especially Ubuntu\Debian.

### Step 1
First you need to install SFML. If the version that you want to install is available in the official repository, then install it using your package manager. For example on Ubuntu/Debian you would use `sudo apt-get install libsfml-dev`.
Alternatively, you could build SFML from source **NOT RECOMMENDED**.   
More information for general setup here [SFML-tutorial](https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/).
### Step 2
In the project's directory you need to link all files using the `g++ *.cpp -c` command, then compile them with `g++ *.o -o quatro-app -lsfml-graphics -lsfml-window -lsfml-system`.
### Step 3
Run the app with `./quatro-app`!

## Features

## Unimplemented features
