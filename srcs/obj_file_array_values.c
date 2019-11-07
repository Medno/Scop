/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:37:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 12:05:34 by pchadeni         ###   ########.fr       */
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
			check_float(&str[i], vec3_assign_coord(&vec[*index], coord));
	
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
	if (!initialize_indices_triplet(parse, &data[i], len))
		return (0);
	nb_faces = count_faces(data);
	if (nb_faces == 4)
	{
		next_sp = ft_strchr(&data[i] + 1, ' ');
		i += next_sp - &data[i];
		if (!initialize_indices_triplet(parse, &data[i], len))
			return (0);
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
		get_nl = ft_strchr(&data[i], '\n');
		if (get_nl == NULL)
			get_nl = data + parse->obj_size;
		if (!ft_strncmp(&data[i], "v ", 2))
			add_vertice(parse->vertices, &data[i], &parse->index_vertices,
				VERTEX);
		else if (!ft_strncmp(&data[i], "vt ", 3))
			add_vertice(parse->vertices_texture, &data[i],
				&parse->index_vertices_texture, TEXTURE);
		else if (!ft_strncmp(&data[i], "vn ", 3))
			add_vertice(parse->vertices_normal, &data[i],
				&parse->index_vertices_normal, NORMAL);
		else if (!ft_strncmp(&data[i], "f ", 2))
			handle_indices_line(parse, &data[i], get_nl - &data[i]);
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
