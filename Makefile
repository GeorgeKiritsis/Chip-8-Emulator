CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_image -I/opt/homebrew/include/SDL2_ttf -D_THREAD_SAFE -std=c99
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_DIR = src
OBJ_DIR = build/debug
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = $(BIN_DIR)/game

all: $(EXECUTABLE)

debug: $(EXECUTABLE) -DDEBUG

$(EXECUTABLE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

exec: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	@echo Cleaning...
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)

.PHONY: all exec clean
