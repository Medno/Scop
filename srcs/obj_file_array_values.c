/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:37:09 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/05 18:57:49 by pchadeni         ###   ########.fr       */
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
	while (&str[i] < get_nl)
	{
		float f = check_float(&str[i], &f);
		if (!(get_esp = ft_strchr(&str[i], ' ')))
			return (print_parser_error(PARSING_MISSING_SPACE));
		i += get_esp - &str[i] + 1;
		printf("Assign_coord ");
		if (get_esp - i > 0)
			check_float(&str[i], vec3_assign_coord(&vec[*index], coord));
		coord += 1;
		if (type == TEXTURE && coord == 2)
			break;
	}
	(*index)++;
	return (1);
}

void	assign_vec3(float *array, t_vec3 vect, t_token_obj tok)
{
	printf("vector = ( %f, %f, %f )\n", vect.x, vect.y, vect.z);
	*array = vect.x;
	*(array + 1) = vect.y;
	if (tok != TEXTURE)
		*(array + 2) = vect.z;
}

void	assign_all_data_index(t_parse_obj *parse, int indice, t_token_obj tok)
{
printf("Start initialize_indices_single_index\n");
printf("indice: %d\n", indice);
	if (tok == VERTEX)
		assign_vec3(&parse->all_data[parse->current_indice * parse->offset_all_data],
			parse->vertices[indice], tok);
	else if (tok == NORMAL)
		assign_vec3(&parse->all_data[
		(parse->current_indice * parse->offset_all_data) + parse->offset_all_data_normal
		], parse->vertices_normal[indice], tok);
	else if (tok == TEXTURE)
		assign_vec3(&parse->all_data[(parse->current_indice * parse->offset_all_data) + parse->offset_all_data_normal + 2],
			parse->vertices_texture[indice], tok);
}

uint8_t	initialize_indices_single_splitted(t_parse_obj *parse, char *str,
	t_token_obj tok)
{
	size_t	i;
	int		indice;
	
	i = 1;
printf("Start initialize_indices_single_splitted\n");
	if (i > (unsigned)parse->obj_size)
		return (print_parser_error(PARSING_NB_FACES));
	indice = ft_atoi(&str[i]) - 1;
	parse->indices[parse->index_indices] = indice;
	parse->index_indices++;
	if (tok == VERTEX)
		parse->current_indice = indice;
	if (indice < 0 || (unsigned)indice > parse->len_vertices)
		return (print_parser_error(PARSING_INDEX_OUT_OF_BOUND));
	assign_all_data_index(parse, indice, tok);
	return (1);
}

uint8_t	initialize_indices_single(t_parse_obj *parse, char *str, int len)
{
	char	*next_slash;
	char	*next_next_slash;

printf("Start handling_indices_line_single\n");
	if (!initialize_indices_single_splitted(parse, str, VERTEX))
		return (0);
	if (parse->len_vertices_normal == 0 && parse->len_vertices_texture == 0)
		return (1);
	next_slash = ft_strchr(str, '/');
	if (next_slash > str + len)
		return (0);
	next_next_slash = ft_strchr(str, '/');
	if (initialize_indices_single_splitted(parse, next_slash, TEXTURE))
		return (0);
	if (next_next_slash < str + len)
		return (initialize_indices_single_splitted(parse, next_next_slash, NORMAL));
	return (1);
	
}

uint8_t	initialize_indices_triplet(t_parse_obj *parse, char *data, int len)
{
	size_t	i;
	char	*next_sp;

	i = 0;
printf("Start handling_indices_line_triplet\n");
	next_sp = ft_strchr(data, ' ');
	while (i < 3)
	{
		if (!initialize_indices_single(parse, next_sp, len))
			return (0);
		next_sp = ft_strchr(next_sp, ' ');
		i++;
	}
	return (1);
}

uint8_t	handle_indices_line(t_parse_obj *parse, char *data, int len)
{
	char	*next_sp;
	uint8_t	nb_faces;
	long	i;

printf("Start handling_indices_line\n");
	next_sp = ft_strchr(data, ' ');
	if (!next_sp)
		return (print_parser_error(PARSING_MISSING_SPACE));
	i = next_sp - data;
	if (!initialize_indices_triplet(parse, &data[i], len))
		return (0);
	nb_faces = count_faces(data);
	if (nb_faces == 4)
	{
		next_sp = ft_strchr(&data[i], ' ');
		i += next_sp - &data[i];
		if (!initialize_indices_triplet(parse, &data[i], len))
			return (0);
	}
	return (1);
}

uint8_t	parse_faces(t_parse_obj *parse, char *data, long current)
{
	long	i;
	long	remaining_len;
	char	*next_nl;
	int		len;

	i = 0;
	remaining_len = parse->obj_size - current;
printf("Parsing Faces...\n");
	while (i < remaining_len)
	{
		next_nl = ft_strchr(&data[i], '\n');
		len = next_nl ? next_nl - &data[i] : ft_strlen(&data[i]);
		if (!handle_indices_line(parse, &data[i], len))
			return (0);
		i += len;
		if (data[i])
			i++;
	}
printf("End of Parsing Faces...\n");
	return (1);
}

uint8_t	get_vertices_values(char *data, t_parse_obj *parse)
{
	long	i;
	char	*get_nl;

	i = 0;
	while (i < parse->obj_size)
	{
		if (!ft_strncmp(&data[i], "v ", 2))
			add_vertice(parse->vertices, &data[i], &parse->index_vertices,
				VERTEX);
		else if (!ft_strncmp(&data[i], "vt ", 3))
			add_vertice(parse->vertices_normal, &data[i],
				&parse->index_vertices_normal, NORMAL);
		else if (!ft_strncmp(&data[i], "vn ", 3))
			add_vertice(parse->vertices_texture, &data[i],
				&parse->index_vertices_texture, TEXTURE);
		else if (!ft_strncmp(&data[i], "f ", 2))
			return (parse_faces(parse, &data[i], i));
		if ((get_nl = ft_strchr(&data[i], '\n')) == NULL)
			return (1); // End of file
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}
