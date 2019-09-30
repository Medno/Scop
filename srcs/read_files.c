/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:08:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 17:08:58 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

char	*read_shader_file(const char *filename)
{
	FILE	*fd;
	char	*res;
	long	file_size;

	if (!(fd = fopen(filename, "r")))
	{
		dprintf(2, "Error: Cannot open shader: %s\n", filename);
		return (NULL);
	}
	fseek(fd, 0L, SEEK_END);
	file_size = ftell(fd);
	fseek(fd, 0L, SEEK_SET);
	if (!(res = ft_strnew(file_size)))
	{
		dprintf(2, "Error: Cannot allocate string for shader: %s\n", filename);
		return (NULL);
	}
	if (!(fread(res, file_size, 1, fd)))
	{
		dprintf(2, "Error: Cannot read shader: %s\n", filename);
		return (NULL);
	}
	fclose(fd);
	return (res);
}
