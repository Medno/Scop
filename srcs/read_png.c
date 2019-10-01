/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:05:54 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/01 16:52:38 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_png.h"

t_img	*init_img(FILE *fd)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	fseek(fd, 0L, SEEK_END);
	img->file_size = ftell(fd);
	fseek(fd, 0L, SEEK_SET);
	img->size_data = 0;
	img->width = 0;
	img->height = 0;
	return (img);
}

uint8_t	check_signature(FILE *fd)
{
	char	input[8];

	if (!fread(&input, 8, 1, fd))
		return (0);
	return (!strncmp(input, "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a", 8));
}

uint8_t	read_header(t_img *img, FILE *fd)
{
	char	h[25];

	if (!fread(&h, 25, 1, fd))
		return (0);
	img->width = (h[8] << 24) | (h[9] << 16) | (h[10] << 8) | h[11];
	img->height = (h[12] << 24) | (h[13] << 16) | (h[14] << 8) | h[15];
	img->bit_depth = h[16];
	if (h[17] == 0)
	{
		img->format = GL_LUMINANCE;
		img->format_index = 1;
	}
	else if (h[17] == 4)
	{
		img->format = GL_LUMINANCE_ALPHA;
		img->format_index = 2;
	}
	else if (h[17] == 2)
	{
		img->format = GL_RGB;
		img->format_index = 3;
	}
	else
	{
		img->format = GL_RGBA;
		img->format_index = 4;
	}
	if (!(img->data = (GLubyte*)malloc(sizeof(GLubyte)
		* img->width * img->height * img->format_index)))
	{
		free(img);
		return (0);
	}
	return (1);
}

uint8_t	read_shunk(FILE *fd, t_img *img)
{
	char		begin[8];
	uint32_t	size_chunk;

	if (!fread(begin, 8, 1, fd))
		return (1);
	size_chunk =
		((begin[0] & 0xFF) << 24) | ((begin[1] & 0xFF) << 16)
		| ((begin[2] & 0xFF) << 8) | (begin[3] & 0xFF);
	if (strncmp(&begin[4], "IDAT", 4))
	{
		fseek(fd, size_chunk + 4, SEEK_CUR);
		return (0);
	}
	if (size_chunk > img->file_size)
		return (1);
	if (!fread(&(img->data[img->file_size]), size_chunk, 1, fd))
		return (1);
	img->file_size += size_chunk;

	fseek(fd, 4, SEEK_CUR);
	return (0);
}

t_img	*new_img(const char *name)
{
	t_img	*img;
	FILE	*fd;

	if (!(fd = fopen(name, "r"))
			|| !(img = init_img(fd)))
		return (NULL);
	if (!check_signature(fd))
	{
		free(img->data);
		free(img);
		fclose(fd);
		return (NULL);
	}
	read_header(img, fd);
	while (!read_shunk(fd, img))
	{
	}
	fclose(fd);
	if (img->file_size == 0)
	{
		free(img->data);
		free(img);
		return (NULL);
	}
	img->data[img->file_size] = '\0';
fwrite(img->data, img->file_size, 1, logger);
	return (img);
}
