/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga_bits_colored_rle.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 12:14:43 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 14:26:31 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

void	read_8_colored_rle(t_texture *texture, GLubyte *ptr, unsigned short c,
		GLubyte *data)
{
	(void)data;
	ptr[0] = texture->tga_header.colormap[(c * 3) + 2];
	ptr[1] = texture->tga_header.colormap[(c * 3) + 1];
	ptr[2] = texture->tga_header.colormap[c * 3];
}

void	read_16_colored_rle(t_texture *texture, GLubyte *ptr, unsigned short c,
		GLubyte *data)
{
	(void)data;
	(void)texture;
	ptr[0] = (GLubyte)(((c & 0x7C00) >> 10) << 3);
	ptr[1] = (GLubyte)(((c & 0x3E0) >> 5) << 3);
	ptr[2] = (GLubyte)(((c & 0x1F) >> 0) << 3);
}

void	read_24_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data)
{
	(void)c;
	(void)tex;
	ptr[0] = data[2];
	ptr[1] = data[1];
	ptr[2] = data[0];
}

void	read_32_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data)
{
	(void)c;
	(void)tex;
	ptr[0] = data[2];
	ptr[1] = data[1];
	ptr[2] = data[0];
	ptr[3] = data[3];
}
