/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_constructors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:19:36 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 17:03:27 by pchadeni         ###   ########.fr       */
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
	parser->len_vertices = 0;
	parser->index_vertices = 0;
	parser->normals = NULL;
	parser->len_normals = 0;
	parser->index_normals = 0;
	parser->textures = NULL;
	parser->len_textures = 0;
	parser->index_textures = 0;
	parser->faces = NULL;
	parser->len_faces = 0;
	parser->offset_data = 6;
	parser->offset_data_normal = 0;
	parser->index_indices = 0;
	parser->data_size = 0;
	return (parser);
}

void			define_offset(t_parser_obj *parser)
{
	if (parser->len_normals != 0)
	{
		parser->offset_data += 3;
		parser->offset_data_normal += 3;
	}
	parser->offset_data += 2;
}

uint8_t			create_vertices_arrays(t_parser_obj *parser)
{
	if (parser->len_vertices
		&& !(parser->vertices = vec3_array(parser->len_vertices)))
		return (print_parser_error(ARRAY_VERTICES));
	if (parser->len_normals
		&& !(parser->normals = vec3_array(parser->len_normals)))
		return (print_parser_error(ARRAY_VERTICES_NORMAL));
	if (parser->len_textures
		&& !(parser->textures = vec3_array(parser->len_textures)))
		return (print_parser_error(ARRAY_VERTICES_TEXTURE));
	parser->data_size = parser->len_faces * 6;
	parser->data_size += parser->len_faces * 2;
	if (parser->len_normals > 0)
		parser->data_size += parser->len_faces * 3;
	if (!(parser->data = (float *)malloc(sizeof(float) * parser->data_size)))
		return (print_parser_error(ARRAY_ALL_DATA));
	define_offset(parser);
	return (1);
}

uint8_t			destroy_parser_obj(t_parser_obj **parser, uint8_t all)
{
	if (all)
		clean_parser(*parser);
	if ((*parser)->data)
		free((*parser)->data);
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
	if (parser->normals)
	{
		free(parser->normals);
		parser->normals = NULL;
	}
	if (parser->textures)
	{
		free(parser->textures);
		parser->textures = NULL;
	}
	if (parser->faces)
	{
		ft_lstdel(&parser->faces, ft_lstclean);
		parser->faces = NULL;
	}
}
