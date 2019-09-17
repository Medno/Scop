# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/08 14:57:58 by pchadeni          #+#    #+#              #
#    Updated: 2019/09/17 16:05:26 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Name of the project------#

NAME = scop

#------All sources------#

MAIN_SRCS = main.c		\
			monitor.c	\
			mat4.c		\
			vec3.c		\
			read_files.c\
			mesh.c	\
			handle_error.c	\
			transform.c	\
			shaders.c
			

OBJ += $(addprefix ./$(OBJ_PATH)/, $(MAIN_SRCS:.c=.o))

#------Includes------#

INCLUDES = ./inc/
CFLAGS += -I$(INCLUDES)
CFLAGS += -I$(LIB_PATH)/$(INCLUDES)
CFLAGS += -I$(HOME)/.brew/include

HEAD = $(INCLUDES)/monitor.h	\
	   $(INCLUDES)/mat4.h		\
	   $(INCLUDES)/vec3.h		\
	   $(INCLUDES)/shaders.h	\
	   $(INCLUDES)/transform.h	\
	   $(INCLUDES)/handle_error.h	\
	   $(INCLUDES)/mesh.h

#------Libraries------#

LDFLAGS += -Llibft -lft
LDFLAGS += -L$(HOME)/.brew/lib -framework OpenGL -lglfw3


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

clean:
	@rm -Rf $(OBJ_PATH)
	@rm -Rf $(TEST_OBJ)
	@echo "$(BOLD_GREEN)$(NAME)$(EOC) clean $(BOLD_GREEN)✓$(EOC)"

cleanlib:
	@make clean -C $(LIB_PATH)

fclean: clean
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
CFLAGS += -Wall -Wextra -Werror

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
