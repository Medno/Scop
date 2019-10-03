/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 12:16:40 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 17:28:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	assign_x_bits(t_texture *tex, int i, int j, t_tga_type type)
{
	unsigned short	color;

	if (type == IMG_8_BITS)
	{
		color = (GLubyte)tex->file_data[j];
		tex->data[(i * 3) + 2] = tex->tga_header.colormap[(color * 3) + 0];
		tex->data[(i * 3) + 1] = tex->tga_header.colormap[(color * 3) + 1];
		tex->data[i * 3] = tex->tga_header.colormap[(color * 3) + 2];
	}
	else if (type == IMG_16_BITS)
	{
		color = tex->data[j] + (tex->file_data[i + 1] << 8);
		tex->data[i * 3] = (GLubyte)(((color & 0x7C00) >> 10) << 3);
		tex->data[(i * 3) + 1] = (GLubyte)(((color & 0x3E0) >> 5) << 3);
		tex->data[(i * 3) + 2] = (GLubyte)(((color & 0x1F) >> 0) << 3);
	}
	else if (type == IMG_24_BITS || type == IMG_32_BITS)
	{
		tex->data[(i * 3) + 2] = tex->file_data[j];
		tex->data[(i * 3) + 1] = tex->file_data[j + 1];
		tex->data[i * 3] = tex->file_data[j + 2];
		if (type == IMG_32_BITS)
			tex->data[(i * 3) + 3] = tex->file_data[j + 3];
	}
}

void	read_tga_bits_colored(t_texture *texture)
{
	GLuint	i;
	int		j;
	GLuint	size;

	i = 0;
	j = 0;
	size = texture->width * texture->height;
	while (i < size)
	{
		assign_x_bits(texture, i, j, texture->img_sub_type);
		i++;
		j += texture->format_nb;
	}
}
