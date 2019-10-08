/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tga.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:38:30 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:19:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_TGA_H
# define READ_TGA_H

# define TGA_HEADER_SIZE 18

typedef struct s_texture	t_texture;

typedef enum	e_tga_type
{
	IMG_8_BITS,
	IMG_16_BITS,
	IMG_24_BITS,
	IMG_32_BITS,
	IMG_8_BITS_GREY,
	IMG_16_BITS_GREY,
	IMG_8_BITS_RLE,
	IMG_16_BITS_RLE,
	IMG_24_BITS_RLE,
	IMG_32_BITS_RLE,
	IMG_8_BITS_GREY_RLE,
	IMG_16_BITS_GREY_RLE,
}				t_tga_type;

void	handle_header_tga(t_texture *texture, GLubyte *p);

void	tga_read_bits_rle(t_texture *texture);
void	handle_non_rle(t_texture *texture, int *j, int loop, GLubyte *ptr);

void	tga_read_bits_colored(t_texture *texture);
void	tga_read_bits_grey(t_texture *texture);

void	read_8_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_16_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_24_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);
void	read_32_colored_rle(t_texture *tex, GLubyte *ptr, unsigned short c,
		GLubyte *data);

#endif
