/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:45:34 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 14:58:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "logger.h"
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include "read_tga.h"

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

GLuint	create_texture(void);

void    print_texture(t_texture *texture, uint8_t log);
void	print_header(t_tga_header header, uint8_t log);
#endif
