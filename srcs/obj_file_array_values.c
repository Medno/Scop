/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:37:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 15:26:09 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	add_vertice(t_vec3 *vec, char *str, size_t *index, t_token_obj type)
{
	int	scanned;

	if (type == TEXTURE)
	{
		scanned = sscanf(str, "vt %f %f\n", &vec[*index].x, &vec[*index].y);
		if (scanned != 2)
			return (0);
	}
	else
	{
		if (type == VERTEX)
			scanned = sscanf(str, "v %f %f %f\n",
				&vec[*index].x, &vec[*index].y, &vec[*index].z);
		else
			scanned = sscanf(str, "vn %f %f %f\n",
				&vec[*index].x, &vec[*index].y, &vec[*index].z);
		if (scanned != 3)
			return (0);
	}
	(*index)++;
	return (1);
}

uint8_t	match_vertice_line(char *data, t_parser_obj *parse)
{
	if (!ft_strncmp(data, "v ", 2))
		return (add_vertice(parse->vertices, data, &parse->index_vertices,
			VERTEX));
	else if (!ft_strncmp(data, "vt ", 3))
		return (add_vertice(parse->textures, data,
			&parse->index_textures, TEXTURE));
	else if (!ft_strncmp(data, "vn ", 3))
	{
		return (add_vertice(parse->normals, data,
			&parse->index_normals, NORMAL));
	}
	return (1);
}

uint8_t	get_vertices_values(char *data, t_parser_obj *parse)
{
	long	i;
	char	*get_nl;

	i = 0;
	while (i < parse->obj_size)
	{
		if (!(get_nl = ft_strchr(&data[i], '\n')))
			get_nl = data + parse->obj_size;
		if (!match_vertice_line(&data[i], parse))
			return (print_parser_error(PARSING_WRONG_FORMAT));
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
