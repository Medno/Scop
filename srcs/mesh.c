#include "mesh.h"

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices)
{
	t_mesh	mesh;

	mesh.count_draw = len_vertices;
	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);
	glGenBuffers(NUM_BUFFERS, mesh.vab);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vab[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, len_vertices * sizeof(t_vec3),
		vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, len_vertices, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
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
}
