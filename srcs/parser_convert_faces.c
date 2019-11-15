/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_convert_faces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:23:48 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/15 16:33:27 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void		assign_vec3(float *array, t_vec3 vect, t_token_obj tok)
{
	*array = vect.x;
	*(array + 1) = vect.y;
	if (tok != TEXTURE)
		*(array + 2) = vect.z;
}

static uint8_t	assign_data(t_parser_obj *parser, t_list *face, uint8_t *i,
	t_token_obj t)
{
	t_vec3	color;
	size_t	indice;
	float	color_value;

	color_value = 0.25f + (0.15f * ((parser->index_indices / 3) % 3));
	color = vec3_new(color_value, color_value, color_value);
	indice = ((int *)(face->content))[*i] - 1;
	if (t == VERTEX && indice < parser->len_vertices)
	{
		assign_vec3(&parser->data[parser->index_indices * parser->offset_data],
			parser->vertices[((int *)(face->content))[*i] - 1], t);
		assign_vec3(&parser->data[(parser->index_indices
			* parser->offset_data) + 3], color, VERTEX);
	}
	else if (t == TEXTURE && indice < parser->len_textures)
		assign_vec3(&parser->data[
			((parser->index_indices + 1) * parser->offset_data) - 2],
			parser->textures[((int *)(face->content))[*i] - 1], t);
	else if (t == NORMAL && indice < parser->len_normals)
		assign_vec3(&parser->data[parser->index_indices * parser->offset_data
			+ 6], parser->normals[((int *)(face->content))[*i] - 1], t);
	else
		return (print_parser_error(PARSING_INDEX_OUT_OF_BOUND));
	(*i)++;
	return (1);
}

uint8_t			add_faces_into_data(t_parser_obj *parser)
{
	t_list	*face;
	uint8_t	i;

	face = parser->faces;
	while (face)
	{
		i = 0;
		while (i < face->content_size / sizeof(int))
		{
			if (!assign_data(parser, face, &i, VERTEX))
				return (0);
			if (parser->len_textures && !assign_data(parser, face, &i, TEXTURE))
				return (0);
			if (parser->len_normals && !assign_data(parser, face, &i, NORMAL))
				return (0);
			parser->index_indices++;
		}
		face = face->next;
	}
	return (1);
}
