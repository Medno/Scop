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

unsigned int	init_texture(void)
{
	unsigned int	texture;
//	t_img			*img;
	t_tga_header	*head;
	uint32_t		i;

	i = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	printf("Creating tga...\n");
	head = new_tga_header("./res/wall_texture.tga");
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
	header->colormap_origin = (short)buffer[3];
	header->colormap_len = (short)buffer[5];
	header->colormap_size = buffer[6];
	header->width = (short)buffer[12];
	header->height = (short)buffer[14];
	header->pixel_depth = buffer[16];

for (int i = 0; i < 18; i++)
	fprintf(logger, "%#x\n", buffer[i]);
fprintf(logger, "cm_type:	%d\ncom_type:	%d\ncm_orig:	%d\ncm_len:		%d\ncm_size:	%d\nwidth:		%d\nheight:		%d\npixel_d:	%d\n",
		header->colormap_type,
	header->compression_type,
	header->colormap_origin,
	header->colormap_len,
	header->colormap_size,
	header->width,
	header->height,
	header->pixel_depth);
	return (header);
}

t_tga_header		*new_tga_header(const char *filename)
{
	FILE			*fd;
	t_tga_header	*header;

	if (!(fd = fopen(filename, "rb")))
		return (NULL);
	header = init_header(fd);
	fclose(fd);
	return (header);
}
