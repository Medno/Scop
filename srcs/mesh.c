/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:12 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 18:10:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices, float *textures, unsigned int len_textures)
{
	t_mesh	mesh;

	mesh.count_draw = len_vertices;
	mesh.len_textures = len_textures;
	glGenVertexArrays(1, &mesh.vao);
	glGenBuffers(NUM_BUFFERS, mesh.vab);
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, len_vertices * sizeof(t_vec3) + (len_textures * sizeof(float)), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, len_vertices * sizeof(t_vec3), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, len_vertices * sizeof(t_vec3),
		len_textures * sizeof(float), textures);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vec3), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vab[TEXTURES_VB]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
			(void*)(len_vertices * sizeof(t_vec3)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
printf("Creation of texture...\n");
	mesh.texture = init_texture();
printf("End of mesh...\n");
//handle_error
	return (mesh);
}

void	draw_mesh(t_mesh mesh)
{
	printf("\tBinding textures...\n");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh.texture->id);
	printf("\tBinding VAO...\n");
	glBindVertexArray(mesh.vao);
	printf("\tDrawing Arrays...\n");
	glDrawArrays(GL_TRIANGLES, 0, mesh.count_draw);
	printf("\tDe-bind...\n");
	glBindVertexArray(0);
}

void	delete_mesh(t_mesh mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
}
