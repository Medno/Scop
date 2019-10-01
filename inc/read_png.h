#ifndef READ_PNG_H
# define READ_PNG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include <GLFW/glfw3.h>

#include "logger.h"

#define MAX_SH 8192

typedef struct	s_img
{
	const char	*name;
	uint32_t	width;
	uint32_t	height;
	uint32_t	bit_depth;
	uint32_t	file_size;
	uint64_t	size_data;
	uint32_t	format;
	uint32_t	format_index;
	GLubyte		*data;
}				t_img;

t_img	*new_img(const char *name);

#endif
