/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:58 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 18:07:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_obj	*init_parser_obj(void)
{
	t_parser_obj	*parser;

	if (!(parser = (t_parser_obj *)malloc(sizeof(t_parser_obj))))
	{
		return (print_error(
			"Error: Cannot allocate memory for parser structure", NULL));
	}
	parser->vertices = NULL;
	parser->vertices_normal = NULL;
	parser->vertices_texture = NULL;
	parser->indices = NULL;
	parser->len_vertices = 0;
	parser->len_vertices_normal = 0;
	parser->len_vertices_texture = 0;
	parser->len_faces = 0;
	parser->index_vertices = 0;
	parser->index_vertices = 0;
	parser->index_vertices_normal = 0;
	parser->index_vertices_texture = 0;
	parser->offset_all_data = 6;
	parser->offset_all_data_normal = 0;
	parser->index_indices = 0;
	parser->all_data_size = 0;
	return (parser);
}

void			define_offset(t_parser_obj *parser)
{
	if (parser->len_vertices_normal != 0)
	{
		parser->offset_all_data += 3;
		parser->offset_all_data_normal += 3;
	}
	parser->offset_all_data += 2;
}

uint8_t			create_vertices_arrays(t_parser_obj *parser)
{
	if (parser->len_vertices
		&& !(parser->vertices = vec3_array(parser->len_vertices)))
		return (print_parser_error(ARRAY_VERTICES));
	if (parser->len_vertices_normal && !(parser->vertices_normal = vec3_array(
		parser->len_vertices_normal)))
		return (print_parser_error(ARRAY_VERTICES_NORMAL));
	if (parser->len_vertices_texture && !(parser->vertices_texture =
		vec3_array(parser->len_vertices_texture)))
		return (print_parser_error(ARRAY_VERTICES_TEXTURE));
	parser->all_data_size = parser->len_faces * 6;
	parser->all_data_size += parser->len_faces * 2;
	if (parser->len_vertices_normal > 0)
		parser->all_data_size += parser->len_faces * 3;
	if (!(parser->all_data = (float *)malloc(
		sizeof(float) * parser->all_data_size)))
		return (print_parser_error(ARRAY_ALL_DATA));
	if (!(parser->indices = (int *)malloc(sizeof(int) * parser->len_faces)))
		return (print_parser_error(ARRAY_INDICES));
	define_offset(parser);
	return (1);
}

uint8_t			destroy_parser_obj(t_parser_obj **parser, uint8_t all)
{
	if (all)
		clean_parser(*parser);
	if ((*parser)->all_data)
		free((*parser)->all_data);
	if (*parser)
	{
		free(*parser);
		*parser = NULL;
	}
	return (0);
}

void			clean_parser(t_parser_obj *parser)
{
	if (parser->vertices)
	{
		free(parser->vertices);
		parser->vertices = NULL;
	}
	if (parser->vertices_normal)
	{
		free(parser->vertices_normal);
		parser->vertices_normal = NULL;
	}
	if (parser->vertices_texture)
	{
		free(parser->vertices_texture);
		parser->vertices_texture = NULL;
	}
	if (parser->indices)
	{
		free(parser->indices);
		parser->indices = NULL;
	}
}
