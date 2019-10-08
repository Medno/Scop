/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_read_bits_colored_nrle.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:41:17 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 14:41:20 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

static void	handle_colored_nrle(t_texture *texture, int *j,
		int loop, GLubyte *ptr)
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

void		handle_non_rle(t_texture *texture, int *j, int loop, GLubyte *ptr)
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
