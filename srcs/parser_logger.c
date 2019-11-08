/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:08:39 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/08 10:38:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_parser_data(t_parser_obj *parser)
{
	printf("========= Parser Data : =========\n");
	printf("Number of vertices : %zu\n", parser->len_vertices);
	printf("Number of normal : %zu\n", parser->len_vertices_normal);
	printf("Number of texture : %zu\n", parser->len_vertices_texture);
	printf("Number of faces : %zu\n", parser->len_faces);
	printf("Number of data : %zu\n", parser->all_data_size);
	printf("Offset between data : %hhu\n", parser->offset_all_data);
	printf("Print of vertices\n");
	for (size_t i = 0; i < parser->len_vertices; i++)
	{
	printf("Print of %zu vertice\n", i);
		printf("Vertice [%zu] = ( %f, %f, %f )\n", i, parser->vertices[i].x, parser->vertices[i].y, parser->vertices[i].z);
	}

	printf("Print of vertices normal\n");
	for (size_t i = 0; i < parser->len_vertices_normal; i++)
		printf("Vertice normal [%zu] = ( %f, %f, %f )\n", i, parser->vertices_normal[i].x, parser->vertices_normal[i].y,parser->vertices_normal[i].z);

	printf("Print of vertices texture\n");
	for (size_t i = 0; i < parser->len_vertices_texture; i++)
		printf("Vertice texture [%zu] = ( %f, %f )\n", i, parser->vertices_texture[i].x, parser->vertices_texture[i].y);

	printf("All Data: \n");
	for (size_t i = 0; i < parser->all_data_size; i++)
		printf("[%zu]: %f\n", i, parser->all_data[i]);
	for (size_t i = 0; i < parser->len_faces; i += 3)
		printf("Face [%zu] = %d, %d, %d\n", i, parser->indices[i], parser->indices[i + 1], parser->indices[i + 2]);
}
