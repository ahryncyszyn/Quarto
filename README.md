# Quarto
## What's Quarto about?
🎲 Quarto is a strategy game played on a 4x4 grid, and the objective is to align 4 pieces with a common attribute:
- color
- shape
- height
- solidity

in a line or in a square. What makes the game interesting is that each player chooses the piece to be used by the next player which allows for additonal strategy and depth.

## Set up
> [!NOTE]
> This project is designed to work on Linux based distributions - especially Ubuntu\Debian.

### Step 1
First you need to install SFML. If the version that you want to install is available in the official repository, then install it using your package manager. For example on Ubuntu/Debian you would use `sudo apt-get install libsfml-dev` in the linux cmd.
Alternatively, you could build SFML from source **NOT RECOMMENDED**.   
More information for general setup here [SFML-tutorial](https://www.sfml-dev.org/tutorials/3.0/getting-started/linux/).
### Step 2
Clone the repository. In the project's directory you need to link all files using the `g++ *.cpp -c` command, then compile them with `g++ *.o -o quarto-app -lsfml-graphics -lsfml-window -lsfml-system`.
### Step 3
Run the app with `./quarto-app`!

## Features
### Multiplayer Mode
2 players can engage in a multiplayer mode with each other. Players take turns placing their pieces and picking the next piece for their opponent
### Advanced Mode 
❗ User can choose to turn on the advanced Quarto ruleset by toggling on\off the "advanced mode" button in the main menu. This ruleset makes the game also account for squares with common attributes.
### Easy Bot
The user can play against an easy difficulty bot. The bot is internally called RandomBot because it chooses its moves at random. It shouldn't be hard to outplay it! Player chooses the bot's first piece.
### Hard Bot
The user can play against a high difficulty bot implemented with an algorithm that makes it evaluate its best moves. Player chooses the bot's first piece.
### Instructions
The user can choose to display a set of instruction if they're not sure how Quarto works.
## Unimplemented features
### Medium Bot
There is no medium difficulty implementation at the time. Only Easy and Hard.
### Bot tournament
We haven't managed to create a tournament where the bots could play against each other.
### Advanced mode bots
Bots currently don't know if the advanced mode is turned on so they might not be able to evaluate moves based on the different ruleset.
### Bugs:
- The win screen window crashes after a few seconds. For now you can just click on "wait" and exit the screen to go back to the main menu.


