/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 14:04:07 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices, float *textures, unsigned int len_textures)
{
	t_mesh	mesh;
	float	*merged;
	
	mesh.count_draw = len_vertices;
	mesh.len_textures = len_textures;
	merged = merge_coordinates(vertices, textures, len_vertices, len_textures);
	if (merged)
	{
		glGenVertexArrays(1, &mesh.vao);
		glGenBuffers(NUM_BUFFERS, mesh.vbo);

		glBindVertexArray(mesh.vao);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo[POSITION_VB]);

		glBufferData(GL_ARRAY_BUFFER, len_vertices * len_textures * 3, merged, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		mesh.texture = create_texture();
		free(merged);
	}
//handle_error
	return (mesh);
}

void	draw_mesh(t_mesh mesh)
{
	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.count_draw);
	glBindVertexArray(0);
}

void	delete_mesh(t_mesh mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo[POSITION_VB]);
}
