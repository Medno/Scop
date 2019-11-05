/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:37:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/05 11:35:05 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	add_vertice(t_vec3 *vec, char *str, size_t *index, e_token_obj type)
{
	int		i;
	char	*get_esp;
	char	*get_nl;

	i = 0;
	get_nl = ft_strchr(str, '\n');
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_parser_error(PARSING_MISSING_SPACE));
	i += get_esp - &str[i] + 1;
	float f = check_float(&str[i], &f);
	printf("Value: %f\n", f);
	if (str[i])
		check_float(&str[i], &vec[*index].x);
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_parser_error(PARSING_MISSING_SPACE));
	i += get_esp - &str[i] + 1;
	if (str[i])
		check_float(&str[i], &vec[*index].y);
	if (type == TEXTURE)
	{
		(*index)++;
		return (1);
	}
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_parser_error(PARSING_MISSING_SPACE));
	i += get_esp - &str[i] + 1;
	if (str[i])
		check_float(&str[i], &vec[*index].z);
	(*index)++;
	return (1);
}

uint8_t	handle_coordinates(t_parse_obj *parse, char *data)
{
	char	*next_sp;

	next_sp = ft_strchr(data, ' ');
	if (!next_sp)
		return (print_parser_error(PARSING_MISSING_SPACE));
	
	if (parse->len_vertices_texture != 0 && parse->len_vertices_normal != 0)
		handle_three_coordinates(parse, &data[i]);
	else if (parse->len_vertices_texture != 0 || parse->len_vertices_normal != 0)
		handle_two_coordinates(parse, &data[i]);
	else
		handle_coordinates(parse, &data[i]);
}
// Check indexes with len etc
// Handle Vec2 for textures;
uint8_t	parse_faces(t_parse_obj *parse, char *data)
{
	//For each lines, get the content of f. Put the values into the final array
	size_t	i;
	char	*next_nl;

	i = 0;
	while (i < parse->obj_len)
	{
		next_nl = ft_strchr(&data[i], '\n');
		handle_coordinates(parse, &data[i]);
		if (next_nl)
			i += next_nl - &data[i];
		else
			i += ft_strlen(&data[i]);
		if (data[i])
			i++;
	}
	return (0);
}

uint8_t	get_vertices_values(char *data, t_parse_obj *parse)
{
	size_t	i;
	char	*get_nl;

	i = 0;
	while (data[i])
	{
		if (!ft_strncmp(&data[i], "v ", 2))
			add_vertice(parse->vertices, &data[i], &parse->index_vertices);
		else if (!ft_strncmp(&data[i], "vt ", 3))
			add_vertice(parse->vertices_normal, &data[i],
				&parse->index_vertices_normal);
		else if (!ft_strncmp(&data[i], "vn ", 3))
			add_vertice(parse->vertices_texture, &data[i],
				&parse->index_vertices_texture);
		else if (!ft_strncmp(&data[i], "f ", 2))
			return (parse_faces(parse, &data[i]));
		if ((get_nl = ft_strchr(&data[i], '\n')) == NULL)
			return (1); // End of file
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
