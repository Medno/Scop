/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:16:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/02 18:55:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	assign_x_bits(t_texture *tex, GLubyte *data, int i, t_tga_type type)
{
	unsigned short	color;

	if (type == IMG_8_BITS)
	{
		color = (GLubyte)*data;
		tex->data[(i * 3) + 2] = tex->colormap[(color * 3) + 0];
		tex->data[(i * 3) + 1] = tex->colormap[(color * 3) + 1];
		tex->data[i * 3] = tex->colormap[(color * 3) + 2];
	}
	else if (type == IMG_16_BITS)
	{
		color = *data + (*(data + 1) << 8);
		tex->data[i * 3] = (GLubyte)(((color & 0x7C00) >> 10) << 3);
		tex->data[(i * 3) + 1] = (GLubyte)(((color & 0x3E0) >> 5) << 3);
		tex->data[(i * 3) + 2] = (GLubyte)(((color & 0x1F) >> 0) << 3);
	}
	else if (type == IMG_24_BITS || type == IMG_32_BITS)
	{
		tex->data[(i * 3) + 2] = *data;
		tex->data[(i * 3) + 1] = *(data + 1);
		tex->data[i * 3] = *(data + 2);
		if (type == IMG_32_BITS)
			tex->data[(i * 3) + 3] = *(data + 3);
	}
}

void	read_tga_bits_colored(t_texture *texture, const GLubyte *ptr)
{
	int		i;
	GLuint	size;

	i = 0;
	size = texture->width * texture->height * texture->format_nb;
	while (i < size)
	{
		assign_x_bits(texture, ptr, i, texture->img_sub_type);
		i++;
		d += texture->format_nb;
	}
}
