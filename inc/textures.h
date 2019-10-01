#ifndef TEXTURES_H
# define TEXTURES_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "read_png.h"

#include "logger.h"

typedef struct	s_texture
{
	GLuint	width;
	GLuint	height;
	GLenum	format;
	GLint	format_nb;
	GLuint	id;
	GLubyte	*data;
}				t_texture;

typedef struct	s_tga_header
{
//	GLubyte	id_len;				//1	0
	GLubyte	colormap_type;		//1	1
	GLubyte	compression_type;	//1	2
	short	colormap_origin;	//2	3
	short	colormap_len;		//2	5
	GLubyte	colormap_size;		//1	6
	short	width;				//2	12
	short	height;				//2	14
	GLubyte	pixel_depth;		//1	16
}				t_tga_header;

unsigned int	init_texture(void);

t_tga_header	*new_tga_header(const char *filename);

#endif
