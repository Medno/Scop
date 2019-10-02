/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits_rle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:49:49 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/02 19:06:45 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	handle_rle(int *j, const GLubyte *data, int loop, GLubyte *ptr)
{
	if ()	
}

void	read_tga_bits_rle(const GLubyte *data, t_texture *texture)
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
		packet_header = data[j];
		++j;
		size_to_loop = 1 + (packet_header & 0x7F);
		if (packet_header & 0x80)
			handle_rle(&j, data, size_to_loop, ptr);
		else
			handle_non_rle(&j, data, size_to_loop, ptr);
		ptr += texture->format_nb * size_to_loop;
	}
}
