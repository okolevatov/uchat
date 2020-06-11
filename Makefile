NAME = klient

SERVER = server

FILES = mx_log_in \
		mx_connection \
		loggin \

SRC_PREFFIX = $(addprefix src/, $(FILES))

HEADER = inc/uchat.h

DEL_SRC = $(addsuffix .c, $(FILES))

SRC = $(addsuffix .c, $(SRC_PREFFIX))

SRC_COMPILE = $(addsuffix .c, $(SRC_PREFFIX))

OBJ = $(addsuffix .o, $(FILES))

CFLAGS = -std=c11 `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`

all: install

install: $(NAME) $(SERVER)

$(NAME) : $(SRC) $(INC)
	@clang $(CFLAGS) -c $(SRC_COMPILE)
	@clang $(CFLAGS) $(OBJ) -o $(NAME)
	@mkdir -p obj
	@cp $(OBJ) obj/
	@rm -rf $(OBJ)

$(SERVER) :
	@clang src/userver.c -o $(SERVER)

uninstall: clean
	@rm -rf $(NAME)
	@rm -rf $(SERVER)

clean:
	@rm -rf obj

reinstall: uninstall install
