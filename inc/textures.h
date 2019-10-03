#ifndef TEXTURES_H
# define TEXTURES_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#define SIZE_TGA_HEADER 18

/*
 *	image_type = 1	->				-> 8 bits	RGB
 *	image_type = 2	->	depth = 16	-> 16 bits	RGB
 *					->	depth = 24	-> 24 bits	RGB
 *					->	depth = 32	-> 32 bits	RGB
 *	image_type = 3	->	depth = 8	-> 8 bits	GREY
 *					->	depth = 16	-> 16 bits	GREY
 *
 *	image_type = 9	->				-> 8 bits	RGB		RLE
 *	image_type = 10	->	depth = 16	-> 16 bits	RGB		RLE
 *					->	depth = 24	-> 24 bits	RGB		RLE
 *					->	depth = 32	-> 24 bits	RGB		RLE
 *	image_type = 11	->	depth = 8	-> 8 bits	GREY	RLE
 *					->	depth = 16	-> 16 bits	GREY	RLE
 
 */

typedef enum	e_tga_type
{
	IMG_8_BITS,
	IMG_16_BITS,
	IMG_24_BITS,
	IMG_32_BITS,
	IMG_8_BITS_GREY,
	IMG_16_BITS_GREY,
	IMG_8_BITS_RLE,
	IMG_16_BITS_RLE,
	IMG_24_BITS_RLE,
	IMG_32_BITS_RLE,
	IMG_8_BITS_GREY_RLE,
	IMG_16_BITS_GREY_RLE,
}				t_tga_type;

typedef enum	e_img_type
{
	IMG_COLORED,
	IMG_GREY,
	IMG_RLE,
	NUM_TYPES
}				t_img_type;

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
	GLubyte	*colormap;
}				t_tga_header;


typedef struct	s_texture
{
	GLuint			id;
	GLuint			width;
	GLuint			height;
	GLenum			format;
	GLint			format_nb;
	GLubyte			*data;
	t_tga_type		img_sub_type;
	t_img_type		img_type;
	GLubyte			*file_data;
	t_tga_header	tga_header;
}				t_texture;

t_texture	*init_texture(void);

t_tga_header	*new_tga_header(const char *filename);
void		handle_header_tga(t_texture *texture, GLubyte *p);

void	read_tga_bits_rle(t_texture *texture);

void	read_tga_bits_colored(t_texture *texture);
void	read_tga_bits_grey(t_texture *texture);

void	read_8_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_16_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_24_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_32_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);

void    print_texture(t_texture *texture, uint8_t log);
void	print_header(t_tga_header header, uint8_t log);
#endif
