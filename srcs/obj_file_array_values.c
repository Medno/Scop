/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:37:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 16:13:19 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	add_vertice(t_vec3 *vec, char *str, size_t *index, t_token_obj type)
{
	int			i;
	char		*get_esp;
	char		*get_nl;
	t_v3_coord	coord;

	i = 0;
	coord = COORD_X;
	get_nl = ft_strchr(str, '\n');
	if (get_nl == NULL)
		get_nl = str + ft_strlen(str);
	while (&str[i] < get_nl && coord <= COORD_Z)
	{
		if (!(get_esp = ft_strchr(&str[i], ' ')))
			return (print_parser_error(PARSING_MISSING_SPACE));
		i += get_esp - &str[i] + 1;
		if (get_esp - i > 0)
			if (!check_float(&str[i], vec3_assign_coord(&vec[*index], coord)))
				return (0);
		coord += 1;
		if (type == TEXTURE && coord == COORD_Z)
			break ;
	}
	(*index)++;
	return (1);
}

uint8_t	handle_indices_line(t_parser_obj *parse, char *data, int len)
{
	char	*next_sp;
	uint8_t	nb_faces;
	long	i;

	next_sp = ft_strchr(data, ' ');
	if (!next_sp)
		return (print_parser_error(PARSING_MISSING_SPACE));
	i = next_sp - data;
	if (!init_indices_triplet(parse, &data[i], len, 0))
		return (0);
	nb_faces = count_faces(data);
	if (nb_faces == 4)
	{
		if (!init_indices_triplet(parse, &data[i], len, 1))
			return (0);
	}
	return (1);
}

uint8_t	match_vertice_line(char *data, t_parser_obj *parse)
{
	if (!ft_strncmp(data, "v ", 2))
		return (add_vertice(parse->vertices, data, &parse->index_vertices,
			VERTEX));
	else if (!ft_strncmp(data, "vt ", 3))
		return (add_vertice(parse->vertices_texture, data,
			&parse->index_vertices_texture, TEXTURE));
	else if (!ft_strncmp(data, "vn ", 3))
	{
		return (add_vertice(parse->vertices_normal, data,
			&parse->index_vertices_normal, NORMAL));
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
			return (0);
		if (!ft_strncmp(&data[i], "f ", 2) && !handle_indices_line(parse,
			&data[i], get_nl - &data[i]))
			return (0);
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
