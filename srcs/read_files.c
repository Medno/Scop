/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:08:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 14:35:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle_error.h"

void	*read_file(const char *filename, const char *opt, long *length_data)
{
	FILE	*fd;
	char	*res;
	long	file_size;

	if (!(fd = fopen(filename, opt)))
		return (print_error("Error: Cannot open: ", filename));
	fseek(fd, 0L, SEEK_END);
	file_size = ftell(fd);
	if (length_data)
		*length_data = file_size;
	fseek(fd, 0L, SEEK_SET);
	if (!(res = ft_strnew(file_size)))
	{
		return (print_error("Error: Cannot allocate string for file: ",
			filename));
	}
	if (!(fread(res, file_size, 1, fd)))
		return (print_error("Error: Cannot read shader: ", filename));
	fclose(fd);
	return (res);
}
