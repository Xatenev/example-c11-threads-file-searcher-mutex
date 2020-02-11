NAME=xfs

CC=gcc
CFLAGS=-Wall
LDFLAGS=-pthread

SRC_DIR=src
OBJ_DIR=build
SRC_FILES=$(shell find $(SRC_DIR)/ -type f -name '*.c')
OBJ_FILES=$(subst $(SRC_DIR),$(OBJ_DIR),$(SRC_FILES:.c=.o))

all: $(NAME)

debug: CFLAGS += -DDEBUG -g
debug: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(OBJ_DIR)/$@ $^ $(LDFLAGS)
	rm -f $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(NAME)

run: 
	./$(OBJ_DIR)/$(NAME) ${args}
