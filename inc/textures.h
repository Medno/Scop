/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:15:25 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <stdio.h>
# include <libft.h>
# include "read_file.h"
# include "logger.h"

# define TGA_HEADER_SIZE 18

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
	GLubyte	colormap_type;
	GLubyte	compression_type;
	short	colormap_origin;
	short	colormap_len;
	GLubyte	colormap_size;
	short	width;
	short	height;
	GLubyte	pixel_depth;
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

GLuint			create_texture(void);

void			handle_header_tga(t_texture *texture, GLubyte *p);

void			tga_read_bits_rle(t_texture *texture);
void			handle_non_rle(t_texture *texture, int *j, int loop,
		GLubyte *ptr);

void			tga_read_bits_colored(t_texture *texture);
void			tga_read_bits_grey(t_texture *texture);

void			read_8_colored_rle(t_texture *tex, GLubyte *ptr,
		unsigned short c, GLubyte *data);
void			read_16_colored_rle(t_texture *tex, GLubyte *ptr,
		unsigned short c, GLubyte *data);
void			read_24_colored_rle(t_texture *tex, GLubyte *ptr,
		unsigned short c, GLubyte *data);
void			read_32_colored_rle(t_texture *tex, GLubyte *ptr,
		unsigned short c, GLubyte *data);

void			print_texture(t_texture *texture, uint8_t log);
void			print_header(t_tga_header header, uint8_t log);
#endif
