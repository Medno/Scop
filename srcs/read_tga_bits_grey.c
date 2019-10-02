/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits_grey.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:55:54 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/02 18:55:55 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	read_tga_8_bits_grey(const GLubyte *data, t_texture *texture)
{
	ft_memcpy(texture->data, data, texture->width * texture->height);
}

void	read_tga_16_bits_grey(const GLubyte *data, t_texture *texture)
{
	int		i;
	int		j;
	GLuint	size;

	i = 0;
	j = 0;
	size = texture->width * texture->height * 2;
	while (i < size)
	{
		texture->data[i * 3] = data[j];
		texture->data[(i * 3) + 1] = data[j + 1];
		i++;
		j += 2;
	}
}
