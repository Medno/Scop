/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:19:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/02 18:54:02 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

static void	init_array_function(void (*f)[](t_texture*, GLubyte*, t_tga_type))
{
	f[IMG_COLORED] = &read_tga_bits_colored;
	f[IMG_GREY] = &read_tga_bits_grey;
	f[IMG_COLORED_RLE] = &read_tga_bits;
	f[IMG_GREY_RLE] = &read_tga_bits;
}

t_texture	*fill_texture(GLubyte *ptr, t_texture *texture)
{
	t_tga_header	header;
	void			(*f)[NUM_TYPES](t_texture*, GLubyte*, t_tga_type);

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	handle_header_tga(texture, &header);
	ptr += SIZE_TGA_HEADER + (GLubyte)ptr[0];
	if (header.colormap_type)
	{
		header.colormap = ptr;
		ptr += header.colormap_len * (header.colormap_size >> 3);
	}
	init_array_function(f);
	if ((texture->data = (GLubyte *)malloc(sizeof(GLubyte) * texture->width
		* texture->height * texture->format_nb)))
		(*f)[texture->img_type](texture, ptr);
	else
	{
		free(texture);
		texture = NULL;
	}
	return (texture);
}

t_texture	*import_texture(const char *filename, t_texture *texture)
{
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
	fclose(fd);
	if (file_data)
	{
		ptr = file_data;
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
	texture = import_texture("./res/wall_texture.tga", texture);
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
