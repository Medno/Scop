/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_indices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:25:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 17:22:39 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	assign_vec3(float *array, t_vec3 vect, t_token_obj tok)
{
	*array = vect.x;
	*(array + 1) = vect.y;
	if (tok != TEXTURE)
		*(array + 2) = vect.z;
}

void	assign_all_data_index(t_parse_obj *parse, int indice, t_token_obj tok)
{
printf("Current indice : %d\n", parse->current_indice);
printf("Indice in all_data: %d\n", parse->current_indice * parse->offset_all_data);
printf("Indice in array: %d\n", indice);
printf("token: %d\n", tok);
	if (tok == VERTEX)
		assign_vec3(&parse->all_data[
			parse->current_indice * parse->offset_all_data],
			parse->vertices[indice], tok);
	else if (tok == NORMAL)
		assign_vec3(&parse->all_data[
			(parse->current_indice * parse->offset_all_data)
			+ 3
			], parse->vertices_normal[indice], tok);
	else if (tok == TEXTURE)
		assign_vec3(&parse->all_data[
			((parse->current_indice + 1) * parse->offset_all_data)
			- 2],
			parse->vertices_texture[indice], tok);
}

uint8_t	init_indices_splitted(t_parse_obj *parse, char *str, t_token_obj tok)
{
	size_t	i;
	int		indice;

	i = 1;
	if (i > (unsigned)parse->obj_size)
		return (print_parser_error(PARSING_NB_FACES));
	indice = ft_atoi(&str[i]) - 1;
	if (tok == VERTEX)
	{
		parse->indices[parse->index_indices] = indice;
		parse->index_indices++;
		parse->current_indice = indice;
	}
	if (indice < 0 || (unsigned)indice > parse->len_vertices)
		return (print_parser_error(PARSING_INDEX_OUT_OF_BOUND));
	assign_all_data_index(parse, indice, tok);
	return (1);
}

uint8_t	initialize_indices_single(t_parse_obj *parse, char *str, int len)
{
	char	*next_slash;
	char	*next_next_slash;

	if (!init_indices_splitted(parse, str, VERTEX))
		return (0);
	if (parse->len_vertices_normal == 0 && parse->len_vertices_texture == 0)
		return (1);
	next_slash = ft_strchr(str, '/');
	if (next_slash > str + len)
		return (0);
	next_next_slash = ft_strchr(next_slash + 1, '/');
	if (!init_indices_splitted(parse, next_slash, TEXTURE))
		return (0);
	if (next_next_slash < str + len)
		return (init_indices_splitted(parse, next_next_slash, NORMAL));
	return (1);
}

uint8_t	initialize_indices_triplet(t_parse_obj *parse, char *data, int len)
{
	size_t	i;
	char	*next_sp;

	i = 0;
	next_sp = ft_strchr(data, ' ');
	while (i < 3)
	{
		if (!initialize_indices_single(parse, next_sp, len))
			return (0);
		next_sp = ft_strchr(next_sp + 1, ' ');
		i++;
	}
	return (1);
}
