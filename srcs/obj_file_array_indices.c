/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file_array_indices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:25:52 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/08 11:52:03 by pchadeni         ###   ########.fr       */
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

void	assign_data_index(t_parser_obj *parser, int indice, t_token_obj tok)
{
	if (tok == VERTEX)
	{
		assign_vec3(&parser->all_data[
			parser->index_indices * parser->offset_all_data],
			parser->vertices[indice], tok);
	}
	else if (tok == NORMAL)
		assign_vec3(&parser->all_data[
			(parser->index_indices * parser->offset_all_data)
			+ 6
			], parser->vertices_normal[indice], tok);
	else if (tok == TEXTURE)
		assign_vec3(&parser->all_data[
			((parser->index_indices + 1) * parser->offset_all_data)
			- 2],
			parser->vertices_texture[indice], tok);
}

uint8_t	init_indices_splitted(t_parser_obj *parser, char *str, t_token_obj tok)
{
	size_t	i;
	int		indice;

	i = 1;
	if (i > (unsigned)parser->obj_size)
		return (print_parser_error(PARSING_NB_FACES));
	indice = ft_atoi(&str[i]) - 1;
	if (tok == VERTEX)
		parser->indices[parser->index_indices] = indice;
printf("Indice: %d, token : %d\n", indice, tok);
	if (indice < 0 || (unsigned)indice > parser->len_vertices)
		return (print_parser_error(PARSING_INDEX_OUT_OF_BOUND));
	assign_data_index(parser, indice, tok);
	return (1);
}

uint8_t	initialize_indices_single(t_parser_obj *parser, char *str, int len)
{
	char	*next_sp;
	char	*next_slash;
	char	*next_next_slash;

	if (!init_indices_splitted(parser, str, VERTEX))
		return (0);
	if (parser->len_vertices_normal == 0 && parser->len_vertices_texture == 0)
		return (1);
	next_slash = ft_strchr(str, '/');
	next_sp = ft_strchr(str + 1, ' ');
	if (next_slash > str + len)
		return (0);
	next_next_slash = ft_strchr(next_slash + 1, '/');
	if (!ft_isdigit(*(next_slash + 1)) && next_next_slash > next_sp)
		return ((uint8_t)print_error("Error: Parser: Missing index", NULL));
	if (*(next_slash + 1) != '/')
		if (next_slash + 1 < str + len
				&& !init_indices_splitted(parser, next_slash, TEXTURE))
			return (0);
	if (!ft_isdigit(*(next_next_slash + 1)) && next_next_slash < next_sp)
		return ((uint8_t)print_error("Error: Parser: Missing index", NULL));
	if (next_next_slash < str + len && next_next_slash < next_sp)
		return (init_indices_splitted(parser, next_next_slash, NORMAL));
	return (1);
}

void	assign_color(t_parser_obj *parser)
{
	t_vec3	color;

	color.x = 0.25f + (0.15f * ((parser->index_indices / 3) % 3));
	color.y = color.x;
	color.z = color.x;
	assign_vec3(&parser->all_data[((parser->index_indices - 1)
		* parser->offset_all_data) + 3], color, VERTEX);
	assign_vec3(&parser->all_data[((parser->index_indices - 2)
		* parser->offset_all_data) + 3], color, VERTEX);
	assign_vec3(&parser->all_data[((parser->index_indices - 3)
		* parser->offset_all_data) + 3], color, VERTEX);
}

uint8_t	init_indices_triplet(t_parser_obj *parser, char *str, int len, int spl)
{
	size_t	i;
	char	*next_sp;

	i = 0;
	next_sp = ft_strchr(str, ' ');
	while (i < 3)
	{
		if (!initialize_indices_single(parser, next_sp, len))
			return (0);
		parser->index_indices++;
		next_sp = ft_strchr(next_sp + 1, ' ');
		if (spl && i == 0)
			next_sp = ft_strchr(next_sp + 1, ' ');
		i++;
	}
	assign_color(parser);
	return (1);
}
