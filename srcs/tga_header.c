/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:09:22 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 16:52:06 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

static void	set_tga_type_rle(t_texture *texture, t_tga_header *header)
{
	texture->img_type = IMG_RLE;
	if (header->compression_type == 9)
		texture->img_sub_type = IMG_8_BITS_RLE;
	else if (header->compression_type == 10)
	{
		if (header->pixel_depth == 16)
			texture->img_sub_type = IMG_16_BITS_RLE;
		else if (header->pixel_depth == 24)
			texture->img_sub_type = IMG_24_BITS_RLE;
		else if (header->pixel_depth == 32)
			texture->img_sub_type = IMG_32_BITS_RLE;
	}
	else if (header->compression_type == 11)
	{
		texture->img_sub_type = header->pixel_depth == 8
			? IMG_8_BITS_GREY_RLE : IMG_16_BITS_GREY_RLE;
	}
	else
		texture->img_sub_type = 0;
}

static void	set_tga_type(t_texture *texture, t_tga_header *header)
{
	texture->img_type = IMG_COLORED;
	if (header->compression_type == 1)
		texture->img_sub_type = IMG_8_BITS;
	else if (header->compression_type == 2)
	{
		if (header->pixel_depth == 16)
			texture->img_sub_type = IMG_16_BITS;
		else if (header->pixel_depth == 24)
			texture->img_sub_type = IMG_24_BITS;
		else if (header->pixel_depth == 32)
			texture->img_sub_type = IMG_32_BITS;
	}
	else if (header->compression_type == 3)
	{
		texture->img_type = IMG_GREY;
		texture->img_sub_type = header->pixel_depth == 8
			? IMG_8_BITS_GREY : IMG_16_BITS_GREY;
	}
	else
		set_tga_type_rle(texture, header);
}

static t_tga_header	init_header(GLubyte *buffer)
{
	t_tga_header	header;

	header.colormap_type = buffer[1];
	header.compression_type = buffer[2];
	header.colormap_origin = (buffer[3] & 0xFF) | ((buffer[4] & 0xFF) << 8);
	header.colormap_len = (buffer[5] & 0xFF) | ((buffer[6] & 0xFF) << 8);
	header.colormap_size = buffer[7];
	header.width = (buffer[12] & 0xFF) | ((buffer[13] & 0xFF) << 8);
	header.height = (buffer[14] & 0xFF) | ((buffer[15] & 0xFF) << 8);
	header.pixel_depth = buffer[16];
print_header(header, 0);
	return (header);
}

void		set_format_tga(t_texture *texture)
{
	if (texture->tga_header.compression_type == 3 
		||texture->tga_header.compression_type == 11)
	{
		texture->format = GL_RGB;
		if (texture->tga_header.pixel_depth == 8)
			texture->format_nb = 1;
		else
			texture->format_nb = 2;
	}
	else
	{
		if (texture->tga_header.pixel_depth <= 24)
		{
			texture->format = GL_RGB;
			texture->format_nb = 3;
		}
		else
		{
			texture->format = GL_RGBA;
			texture->format_nb = 4;
		}
	}
printf("Values for RGB : %d, RGBA: %d\n", GL_RGB, GL_RGBA);
}
//UPDATE IT into glTexParameteriv
void		handle_header_tga(t_texture *texture, GLubyte *p)
{
	texture->tga_header = init_header(p);
	texture->width = texture->tga_header.width;
	texture->height = texture->tga_header.height;
	set_tga_type(texture, &texture->tga_header);
	set_format_tga(texture);
print_texture(texture, 0);
}
