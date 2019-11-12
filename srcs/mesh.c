/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/09 13:48:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

uint8_t	create_mesh(const char *filename, t_mesh *mesh)
{
	t_parser_obj	*parser;
	
	if (!(parser = parse_obj_file(filename)))
		return (0);
	mesh->count_draw = parser->len_faces;
	mesh->len_textures = parser->len_vertices_texture;
	if (parser)
	{
		glGenVertexArrays(1, &mesh->vao);
		glGenBuffers(NUM_BUFFERS, mesh->vbo);

		glBindVertexArray(mesh->vao);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[POSITION_VB]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * parser->all_data_size,
			parser->all_data, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE,
			parser->offset_all_data * sizeof(float), (void *)0);

//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[EBO]);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * parser->len_faces, parser->indices, GL_STATIC_DRAW); 

		glEnableVertexAttribArray(0);
		if (parser->len_vertices_texture > 0)
		{
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE,
				parser->offset_all_data * sizeof(float),
				(void *)((parser->offset_all_data - 2) * sizeof(float)));
			glEnableVertexAttribArray(1);
		}
		glBindVertexArray(0);
		mesh->texture = create_texture();
	}
//print_parser_data(parser);
	if (parser)
		destroy_parser_obj(parser);
//handle_error
	return (1);
}

void	draw_mesh(t_mesh mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.count_draw);
//	glDrawElements(GL_TRIANGLES, mesh.count_draw, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	delete_mesh(t_mesh mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo[EBO]);
	glDeleteBuffers(1, &mesh.vbo[POSITION_VB]);
}
