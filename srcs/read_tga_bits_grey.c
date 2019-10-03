/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits_grey.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:55:54 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 14:20:22 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	read_tga_8_bits_grey(t_texture *texture)
{
	ft_memcpy(texture->data, texture->file_data,
			texture->width * texture->height);
}

void	read_tga_16_bits_grey(t_texture *texture)
{
	GLuint	i;
	int		j;
	GLuint	size;

	i = 0;
	j = 0;
	size = texture->width * texture->height * 2;
	while (i < size)
	{
		texture->data[i * 3] = texture->file_data[j];
		texture->data[(i * 3) + 1] = texture->file_data[j + 1];
		i++;
		j += 2;
	}
}

void	read_tga_bits_grey(t_texture *texture)
{
	if (texture->img_sub_type == IMG_8_BITS_GREY)
		read_tga_8_bits_grey(texture);
	else
		read_tga_16_bits_grey(texture);

}
