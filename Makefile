NAME		= app

CC			= gcc
BUILDDIR	= build/

SRC			= $(wildcard *.c)
OBJ			= $(patsubst %.c, $(BUILDDIR)%.o, $(SRC))
DEP			= $(OBJ:.o=.d)

DEPFLAGS	= -MMD -MP
INCLUDES	= -I.

CFLAGS		= -Wall -Wextra -pedantic
DBGFLAGS	= -g -O0 -DDEBUG
RELFLAGS	= -O2
SANFLAGS	= -fsanitize=address -fno-omit-frame-pointer

# === Build modes === #
BUILD ?= release

ifeq ($(BUILD),debug)
	CFLAGS += $(DBGFLAGS) $(SANFLAGS)
endif

ifeq ($(BUILD),release)
	CLAGS += $(RELFLAGS)
endif

# === Targets === #

all:		$(NAME)

$(NAME): $(OBJ)
			$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)%.o: %.c | $(BUILDDIR)
			$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

$(BUILDDIR):
			mkdir -p $@

-include $(DEP)

clean:
			rm -rf $(BUILDDIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

debug:
			$(MAKE) BUILD=debug

release:
			$(MAKE) BUILD=release

.PHONY:		all clean fclean re debug release

