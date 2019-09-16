#ifndef MESH_H
# define MESH_H

#include <GL/glew.h>
#include "vec3.h"

enum
{
	POSITION_VB,

	NUM_BUFFERS
};

typedef struct	s_mesh
{
	GLuint			vao;
	GLuint			vab[NUM_BUFFERS];
	unsigned int	count_draw;
}				t_mesh;

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices);
void	delete_mesh(t_mesh mesh);
void	draw_mesh(t_mesh mesh);

#endif
