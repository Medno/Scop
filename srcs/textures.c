/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:41 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/01 18:16:59 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

t_texture	init_texture(void)
{
	t_texture		texture;
//	t_img			*img;
	t_tga_header	*head;
	uint32_t		i;

	i = 0;
	glGenTextures(1, &texture.id);
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	printf("Creating tga...\n");
	fill_texture("./res/wall_texture.tga", &texture);
/**	printf("Importing png\n");
	img = new_img("./res/wood5.png");
	if (img)
	{
	printf("TexImage2d...\n");
		glTexImage2D(GL_TEXTURE_2D, 0, img->format_index, img->width, img->height, 0,
			img->format, GL_UNSIGNED_BYTE, img->data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	*/
	return (texture);
}

static t_tga_header	*init_header(FILE *fd)
{
	char			buffer[18];
	t_tga_header	*header;

	if (!(fread(buffer, 18, 1, fd)))
		return (NULL);
	if (!(header = (t_tga_header *)malloc(sizeof(t_tga_header))))
		return (NULL);
	header->colormap_type = buffer[1];
	header->compression_type = buffer[2];
	header->colormap_origin = (buffer[3] & 0xFF) | ((buffer[4] & 0xFF) << 8);
	header->colormap_len = (buffer[5] & 0xFF) | ((buffer[6] & 0xFF) << 8);
	header->colormap_size = buffer[7];
	header->width = (buffer[12] & 0xFF) | ((buffer[13] & 0xFF) << 8);
	header->height = (buffer[14] & 0xFF) | ((buffer[15] & 0xFF) << 8);
	header->pixel_depth = buffer[16];

fprintf(logger, "cm_type:	%d\ncom_type:	%d\ncm_orig:	%d\ncm_len:		%d\ncm_size:	%d\nwidth:		%d\nheight:		%d\npixel_d:	%d\n",
	header->colormap_type, header->compression_type, header->colormap_origin, header->colormap_len,
	header->colormap_size, header->width, header->height, header->pixel_depth);
	return (header);
}

static void	fill_type_texture(t_tga_header *head, t_texture *texture)
{
  texinfo->width = header->width;
  texinfo->height = header->height;

	if (head->compression_type == 11 && header->pixel_depth == 8)
	{
		texture->format = GL_LUMINANCE;
		texture->format_nb = 1;
	}
	else if (head->compression_type == 11)
	{
		texture->format = GL_LUMINANCE_ALPHA;
		texture->format_nb = 2;
	}
	else if (head->compression_type == 10 && header->pixel_depth == 8)
	{
		texture->format = GL_RGB;
		texture->format_nb = 3;
	}
	else if (head->compression_type == 10)
	{
		texture->format = GL_RGBA;
		texture->format_nb = 4;
	}
}

void		fill_texture(const char *filename, t_texture *texture)
{
	FILE			*fd;
	t_tga_header	*header;

	if (!(fd = fopen(filename, "rb")))
		return (NULL);
	header = init_header(fd);
	fill_type_texture(header, texture);
	fclose(fd);
	return (header);
}
