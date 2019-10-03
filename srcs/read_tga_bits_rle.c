/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits_rle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:49:49 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 14:44:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

static int	set_new_coord(t_texture *texture)
{
	if (texture->img_sub_type == IMG_8_BITS_RLE)
		return (1);
	else if (texture->img_sub_type == IMG_16_BITS_RLE)
		return (2);
	else if (texture->img_sub_type == IMG_24_BITS_RLE)
		return (3);
	return (4);
}

void	handle_colored_nrle(t_texture *texture, int *j, int loop, GLubyte *ptr)
{
	int				i;
	unsigned short	color;
	void			(*f[4])(t_texture *, GLubyte *, unsigned short, GLubyte *);

	i = 0;
	f[0] = &read_8_colored_rle;
	f[1] = &read_16_colored_rle;
	f[2] = &read_24_colored_rle;
	f[3] = &read_32_colored_rle;
	while (i < loop)
	{
		color = (texture->img_sub_type == IMG_8_BITS_GREY_RLE)
			? texture->file_data[*j]
			: texture->file_data[*j] + (texture->file_data[*j] << 8);
		f[(texture->tga_header.pixel_depth / 8) - 1](texture, ptr, color,
				&texture->file_data[*j]);
		ptr += texture->format_nb;
		i++;
		(*j) += texture->tga_header.pixel_depth / 8;
	}
}

void	handle_non_rle(t_texture *texture, int *j, int loop, GLubyte *ptr)
{
	int		i;

	i = 0;
	if (!(texture->img_sub_type == IMG_8_BITS_GREY_RLE
		|| texture->img_sub_type == IMG_16_BITS_GREY_RLE))
		handle_colored_nrle(texture, j, loop, ptr);
	else
	{
		ft_memcpy(ptr, texture->file_data + *j,
				loop * sizeof(GLubyte) * texture->format_nb);
		(*j) += loop * texture->format_nb;
	}
}



void	handle_colored_rle(t_texture *texture, int *j, int loop, GLubyte *ptr)
{
	int				i;
	unsigned short	color;
	void			(*f[4])(t_texture *, GLubyte *, unsigned short, GLubyte *);

	i = 0;
	f[0] = &read_8_colored_rle;
	f[1] = &read_16_colored_rle;
	f[2] = &read_24_colored_rle;
	f[3] = &read_32_colored_rle;
	color = (texture->img_sub_type == IMG_8_BITS_GREY_RLE)
		? texture->file_data[*j]
		: texture->file_data[*j] + (texture->file_data[*j] << 8);
	(*j) += set_new_coord(texture);
	while (i < loop)
	{
		f[texture->tga_header.pixel_depth / 8 - 1](texture, ptr, color,
				&texture->file_data[*j]);
		ptr += texture->format_nb;
		i++;
	}
}

void	handle_rle(t_texture *texture, int *j, int loop, GLubyte *ptr)
{
	GLubyte color;
	GLubyte alpha;
	int		i;

	i = 0;
	if (!(texture->img_sub_type == IMG_8_BITS_GREY_RLE
		|| texture->img_sub_type == IMG_16_BITS_GREY_RLE))
		handle_colored_rle(texture, j, loop, ptr);
	else
	{
		color = texture->file_data[*j];
		if (texture->img_sub_type == IMG_8_BITS_GREY_RLE)
			ft_memset(ptr, color, loop);
		else
		{
			alpha = texture->file_data[*(j + 1)];
			(*j)++;
			while (i < loop) 
			{
				ptr[i * 2] = color;
				ptr[(i * 2) + 1] = alpha;
				i++;
			}
		}
		(*j)++;
	}
}

void	read_tga_bits_rle(t_texture *texture)
{
	int		j;
	int		size;
	int		size_to_loop;
	GLubyte	packet_header;
	GLubyte	*ptr;

	j = 0;
	size = texture->width * texture->height;
	ptr = texture->data;
	while (ptr < texture->data + size)
	{
		packet_header = texture->file_data[j];
		++j;
		size_to_loop = 1 + (packet_header & 0x7F);
		if (packet_header & 0x80)
			handle_rle(texture, &j, size_to_loop, ptr);
		else
			handle_non_rle(texture, &j, size_to_loop, ptr);
		ptr += texture->format_nb * size_to_loop;
	}
}
