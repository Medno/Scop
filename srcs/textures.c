/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:19:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 17:08:23 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

t_texture	*tga_read_bits(GLubyte *ptr, t_texture *texture)
{
	void	(*f[NUM_TYPES])(t_texture*);

	if (!(texture = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	handle_header_tga(texture, ptr);
	ptr += TGA_HEADER_SIZE + (GLubyte)ptr[0];
	texture->file_data = ptr;
	if (texture->tga_header.colormap_type)
	{
		texture->tga_header.colormap = ptr;
		ptr += texture->tga_header.colormap_len
			* (texture->tga_header.colormap_size >> 3);
	}
	f[IMG_COLORED] = &tga_read_bits_colored;
	f[IMG_GREY] = &tga_read_bits_grey;
	f[IMG_RLE] = &tga_read_bits_rle;
	if ((texture->data = (GLubyte *)malloc(sizeof(GLubyte) * texture->width
		* texture->height * texture->format_nb)))
	{
		f[texture->img_type](texture);
		return (texture);
	}
	free(texture);
	return (NULL);
}

t_texture	*read_texture_file(const char *filename)
{
	t_texture	*texture;
	GLubyte		*file_data;
	GLubyte		*ptr;

	texture = NULL;
	file_data = (GLubyte *)read_file(filename, "rb", NULL);
	if (file_data)
	{
		ptr = file_data;
		texture = tga_read_bits(ptr, texture);
		free(file_data);
	}
	return (texture);
}

static void	define_texture_img(char const *filename)
{
	t_texture	*texture;

	texture = read_texture_file(filename);
	if (texture && texture->data)
	{
		if (texture->data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, texture->format, texture->width,
				texture->height, 0, texture->format,
				GL_UNSIGNED_BYTE, texture->data);
			free(texture->data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		free(texture);
	}
}

GLuint		create_texture(void)
{
	GLuint		id;
	uint32_t	i;

	i = 0;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	define_texture_img("./res/cat.tga");
	return (id);
}
