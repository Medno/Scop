/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:19:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/04 16:27:19 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"


t_texture	*fill_texture(GLubyte *ptr, t_texture *texture)
{
	void			(*f[NUM_TYPES])(t_texture*);

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	handle_header_tga(texture, ptr);
	ptr += SIZE_TGA_HEADER + (GLubyte)ptr[0];
	texture->file_data = ptr;
	if (texture->tga_header.colormap_type)
	{
		texture->tga_header.colormap = ptr;
		ptr += texture->tga_header.colormap_len
			* (texture->tga_header.colormap_size >> 3);
	}
	f[IMG_COLORED] = &read_tga_bits_colored;
	f[IMG_GREY] = &read_tga_bits_grey;
	f[IMG_RLE] = &read_tga_bits_rle;
	if ((texture->data = (GLubyte *)malloc(sizeof(GLubyte) * texture->width
		* texture->height * texture->format_nb)))
	{
		f[texture->img_type](texture);
		return (texture);
	}
	free(texture);
	return(NULL);
}

t_texture	*import_texture(const char *filename)
{
	t_texture		*texture;
	GLubyte	*file_data;
	GLubyte	*ptr;
	FILE	*fd;
	long	file_size;

	texture = NULL;
	if (!(fd = fopen(filename, "rb")))
		return (NULL);
	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	file_data = (GLubyte *)malloc(sizeof(GLubyte) * file_size);
printf("Filesize : %ld\n", file_size);
	fread(file_data, sizeof(GLubyte), file_size, fd);
	fclose(fd);
	if (file_data)
	{
		ptr = file_data;
printf("Start filling\n");
		texture = fill_texture(ptr, texture);
		free(file_data);
	}
	return (texture);
}

t_texture	*init_texture(void)
{
	t_texture		*texture;
	uint32_t		i;

	i = 0;
	printf("Creating tga...\n");
	texture = import_texture("./res/wall_texture.tga");
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, texture->format, texture->width, texture->height, 0,
	texture->format, GL_UNSIGNED_BYTE, texture->data);

	glGenerateMipmap(GL_TEXTURE_2D);

//FREE TEXTURE
	return (texture);
}


void	print_header(t_tga_header header, uint8_t log)
{
	if (log)
		fprintf(logger, "cm_type:	%d\ncom_type:	%d\ncm_orig:	%d\ncm_len:		%d\ncm_size:	%d\nwidth:		%d\nheight:		%d\npixel_d:	%d\n",
	header.colormap_type, header.compression_type, header.colormap_origin, header.colormap_len,
	header.colormap_size, header.width, header.height, header.pixel_depth);
	else
		printf("cm_type:	%d\ncomp_type:	%d\ncm_orig:	%d\ncm_len:		%d\ncm_size:	%d\nwidth:		%d\nheight:		%d\npixel_d:	%d\n",
	header.colormap_type, header.compression_type, header.colormap_origin, header.colormap_len,
	header.colormap_size, header.width, header.height, header.pixel_depth);
}

void	print_texture(t_texture *texture, uint8_t log)
{
	if (log)
	{
		fprintf(logger, "Start debugging Texture...\n");
		fprintf(logger, "Width :		%d\n", texture->width);
		fprintf(logger, "Height :	%d\n", texture->height);
		fprintf(logger, "format :	%d\n", texture->format);
		fprintf(logger, "format_nb :	%d\n", texture->format_nb);
		print_header(texture->tga_header, log);
		for(unsigned int i = 0; i < texture->height * texture->width; i++) {
			fprintf(logger, "%x ", texture->data[i]);
			if (!(i % texture->width) && i)
				fprintf(logger, "\n");
		}
		fprintf(logger, "End debugging Texture...\n");
	}
	else
	{
		printf("Start debugging Texture...\n");
		printf("Width :		%d\n", texture->width);
		printf("Height :	%d\n", texture->height);
		printf("format :	%d\n", texture->format);
		printf("format_nb :	%d\n", texture->format_nb);
		print_header(texture->tga_header, log);
		printf("End debugging Texture...\n");
	}
}
