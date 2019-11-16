# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 18:55:23 by pchadeni          #+#    #+#              #
#    Updated: 2019/11/16 17:32:48 by pchadeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------Name of the project------#

NAME = scop

#------All sources------#

MAIN_SRCS = main.c		\
			callbacks.c	\
			input_manager.c	\
			input_manager_2.c	\
\
			glfw_constructors.c	\
			monitor_constructors.c	\
			mesh.c	\
			view_constructors.c	\
			view_updates.c	\
			model_constructors.c	\
			model_transformations.c	\
			textures.c	\
			shaders_updates.c	\
			shaders_constructors.c	\
\
			mat4_basic_operations.c		\
			mat4_constructors.c		\
\
			vec3_basic_operations.c		\
			vec3_constructors.c		\
			vec3_geometry.c		\
\
			tga_read_bits.c	\
			tga_read_bits_colored_nrle.c	\
			tga_read_bits_colored_rle.c	\
			tga_read_bits_grey.c	\
			tga_read_bits_rle.c	\
			tga_header.c	\
\
			obj_file_array_values.c	\
			obj_handle_faces.c	\
\
			parser_constructors.c	\
			parser_errors.c	\
			parser_obj_file.c	\
			parser_convert_faces.c	\
			find_limits.c \
\
			handle_error.c	\
			read_files.c\
			parse_float.c
			
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
	   $(INCLUDES)/model.h	\
	   $(INCLUDES)/view.h	\
	   $(INCLUDES)/read_file.h	\
	   $(INCLUDES)/handle_error.h	\
	   $(INCLUDES)/textures.h	\
	   $(INCLUDES)/parser.h	\
	   $(INCLUDES)/mesh.h

#------Libraries------#

LDFLAGS += -Llibft -lft
LDFLAGS += -L$(HOME)/.brew/lib -framework OpenGL -lglfw


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
	@$(CC) $(CFLAGS) $(LDFLAGS) $(GLFLAGS) $(INC) -o $(NAME) $(OBJ)
	@printf "$(BOLD_GREEN)⤖     $(NAME)$(EOC) created $(BOLD_GREEN)✓$(EOC)\n"

$(OBJ_PATH)/%.o: $(SRCS_PATH)/%.c $(HEAD)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
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
	@echo "$(BOLD_GREEN)$(NAME)$(EOC) fclean $(BOLD_GREEN)✓$(EOC)"

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
