##
# 2048
#
# @file
# @version 0.1

SRCS = $(wildcard src/*.c)
AUXFILES = leaderboard savefile
TARGET = 2048

CC = gcc
LFLAGS = -Wall -lncurses

build:
	$(CC) $(LFLAGS) $(SRCS) -o $(TARGET)

run: build
	./2048

clean:
	-rm $(TARGET) $(AUXFILES)

.PHONY: pack run clean build
# end
