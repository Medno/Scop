/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 17:40:46 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

void	enable_buffer(GLuint index, GLint size, GLsizei stride, size_t pointer)
{
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE,
		stride * sizeof(float), (void *)(pointer * sizeof(float)));
	glEnableVertexAttribArray(index);
}

t_mesh	*create_mesh(const char *filename)
{
	t_parser_obj	*parser;
	t_mesh			*mesh;

	if (!(parser = parse_obj_file(filename))
		|| !(mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	mesh->count_draw = parser->len_faces;
	mesh->len_textures = parser->len_textures;
	mesh->len_normals = parser->len_normals;
	glGenVertexArrays(1, &(mesh->vao));
	glGenBuffers(NUM_BUFFERS, mesh->vbo);
	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * parser->data_size,
			parser->data, GL_STATIC_DRAW);
	enable_buffer(0, 3, parser->offset_data, 0);
	enable_buffer(1, 3, parser->offset_data, 3);
	enable_buffer(2, 2, parser->offset_data, parser->offset_data - 2);
	if (parser->len_normals > 0)
		enable_buffer(3, 3, parser->offset_data, parser->offset_data - 5);
	glBindVertexArray(0);
	mesh->texture = create_texture();
	destroy_parser_obj(&parser, 0);
	return (mesh);
}

void	draw_mesh(t_mesh mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.count_draw);
	glBindVertexArray(0);
}

void	delete_mesh(t_mesh *mesh)
{
	glDeleteVertexArrays(1, &(mesh->vao));
	glDeleteBuffers(1, &(mesh->vbo[POSITION_VB]));
	free(mesh);
}
