# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2019/09/10 18:17:46 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Name of the project------#

NAME = scop

#------All sources------#

MAIN_SRCS = monitor.c	\
			main.c

OBJ += $(addprefix ./$(OBJ_PATH)/, $(MAIN_SRCS:.c=.o))

#------Includes------#

INCLUDES = ./inc/
CFLAGS += -I$(INCLUDES)
CFLAGS += -I$(LIB_PATH)/$(INCLUDES)
CFLAGS += $(shell sdl2-config --cflags)

HEAD = $(INCLUDES)/monitor.h

#------Libraries------#

LDFLAGS += -Llibft -lft
LDFLAGS += $(shell sdl2-config --libs)

GLFLAGS = -framework GLUT -framework OpenGL -Wno-deprecated

LIB = $(LIB_PATH)/libft.a

#------Path------#

SRCS_PATH = srcs
OBJ_PATH  = obj
LIB_PATH  = libft

#------Main rules------#

all: $(OBJ_PATH) makelib $(NAME)

$(NAME): $(LIB) $(OBJ)
	@printf "\33[2KObjects created $(BOLD_GREEN)✓$(EOC)\n"
	@printf "Start making $(NAME)...\n"
	$(CC) $(CFLAGS) $(LDFLAGS) $(GLFLAGS) $(INC) -o $(NAME) $(OBJ)
	@printf "$(BOLD_GREEN)⤖     $(NAME)$(EOC) created $(BOLD_GREEN)✓$(EOC)\n"

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(HEAD)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@printf " $(COL_GREEN)[OK]$(EOC) $(COL_YELLOW)Compiling:$(EOC) $<\r"

makelib:
	@make -C $(LIB_PATH) NOERR=$(NOERR) DEV=$(DEV) SAN=$(SAN)

clean: cleanlib
	@rm -Rf $(OBJ_PATH)
	@rm -Rf $(TEST_OBJ)
	@echo "$(BOLD_GREEN)$(NAME)$(EOC) clean $(BOLD_GREEN)✓$(EOC)"

cleanlib:
	@make clean -C $(LIB_PATH)

fclean: fcleanlib clean
	@rm -Rf $(NAME) $(LINK)
	@echo "$(BOLD_GREEN)$(NAME) $(EOC) fclean $(BOLD_GREEN)✓$(EOC)"

fcleanlib:
	@make fclean -C $(LIB_PATH)

re: fclean all

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@printf "$(OBJ_PATH) created\n"

#------Compilation's flags------#

CC = gcc

# flags
CFLAGS += -Wall -Wextra

ifneq ($(NOERR),yes)
CFLAGS += -Werror
endif

ifeq ($(DEV),yes)
CFLAGS += -g
endif

ifeq ($(SAN),yes)
CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

#------Define colors------#

BOLD_GREEN = \033[01;32m
COL_GREEN = \033[0;32m
COL_YELLOW = \033[0;33m
EOC = \033[0m

.PHONY: all re fclean clean
