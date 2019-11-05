/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:58 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/05 11:33:40 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parse_obj	*init_parse_obj(void)
{
	t_parse_obj	*parse;
	if (!(parse = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		return ((uint8_t)print_error("Error: Cannot allocate memory for parser structure", NULL));
	parser->vertices = NULL;
	parser->vertices_normal = NULL;
	parser->vertices_texture = NULL;
	parser->indices = NULL;
	parser->face_type = V_1;
	parser->len_vertices = 0;
	parser->len_vertices_normal = 0;
	parser->len_vertices_texture = 0;
	parser->len_faces = 0;
	parser->index_vertices = 0;
	parser->index_vertices_normal = 0;
	parser->index_vertices_texture = 0;
}

uint8_t	create_vertices_arrays(t_parse_obj *parse)
{
	if (!(parse->vertices =
		(t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices)))
		return (print_parser_error(ARRAY_VERTICES));
	if (!(parse->vertices_normal =
		(t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices_normal)))
		return (print_parser_error(ARRAY_VERTICES_NORMAL));
	if (!(parse->vertices_texture =
		(t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices_texture)))
		return (print_parser_error(ARRAY_VERTICES_TEXTURE));
	if (!(parse->all_data = (float *)malloc(sizeof(float) *
		((3 * parse->len_vertices) + (2 * parse->len_vertices) +
		 (3 * parse->len_vertices)))))
		return (print_parser_error(ARRAY_ALL_DATA));
	if (!(parse->indices_data = (int *)malloc(sizeof(int) * parse->len_faces)))
		return (print_parser_error(ARRAY_INDICES));
	return (1);
}


void	print_parser_data(t_parse_obj *parser)
{
//	printf("Vertices : ");
	printf("Number of vertices : %zu\n", parser->len_vertices);
	printf("Number of normal : %zu\n", parser->len_vertices_normal);
	printf("Number of texture : %zu\n", parser->len_vertices_texture);
	printf("Number of faces : %zu\n", parser->len_faces);
	for (size_t i = 0; i < parser->index_vertices; i++)
		printf("Vertice [%zu] = ( %f, %f, %f )\n", i, parser->vertices[i].x, parser->vertices[i].y, parser->vertices[i].z);
	for (size_t i = 0; i < parser->index_vertices_normal; i++)
		printf("Vertice normal [%zu] = ( %f, %f, %f )\n", i, parser->vertices_normal[i].x, parser->vertices_normal[i].y,parser->vertices_normal[i].z);
	for (size_t i = 0; i < parser->index_vertices_texture; i++)
		printf("Vertice texture [%zu] = ( %f, %f, %f )\n", i, parser->vertices_texture[i].x, parser->vertices_texture[i].y, parser->vertices_texture[i].z);
}
