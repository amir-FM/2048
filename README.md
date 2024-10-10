# 2048

A clone of the classic game made entirely in **C** and made to be played in the terminal / cmd. With modularisation in mind the project is made to be easily modifiable.

![demo](https://github.com/user-attachments/assets/8dee0d1f-ed4a-4354-8fe2-6173500af5fc)

## Support

The project has been developed on linux, so support for any other platform is not guaranteed.

The project needs **ncurses** library, to work properly.

## Installation

*Dependencies: gcc or any C compiler (in this case you need to edit the Makefile)*

``` sh
git clone https://github.com/amir-FM/2048 [instalation directory]
cd ./[instalation directory]
make
./2048
```

## Project Structure

*info: graphics are hard-coded into the source files. (logo and leaderboard texts)*

- main.c - connects all modules
- menu.c - menu items + logo
- game.c - the game panel
- fileHandler.c - handles savefile and leaderboard
- colors.c - colorscheme for the game
- panels.c - auxilary panels for the game
- keys.c - keyboard scheme
