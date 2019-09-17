/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/17 15:52:17 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices)
{
	t_mesh	mesh;

	dprintf(2, "mesh : %u\n", len_vertices);
	mesh.count_draw = len_vertices / 3;
	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);
	glGenBuffers(NUM_BUFFERS, mesh.vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, len_vertices * sizeof(t_vec3),
		vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
//handle_error
	return (mesh);
}

void	draw_mesh(t_mesh mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.count_draw / 3);
	glBindVertexArray(0);
}

void	delete_mesh(t_mesh mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
}
