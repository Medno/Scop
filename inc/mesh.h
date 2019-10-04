/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:20 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/03 18:10:34 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include "vec3.h"
#include "handle_error.h"
#include "textures.h"

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
	t_texture		*texture;
	unsigned int	len_textures;
}				t_mesh;

t_mesh	create_mesh(t_vec3 *vertices, unsigned int len_vertices, float *textures, unsigned int len_textures);
void	delete_mesh(t_mesh mesh);
void	draw_mesh(t_mesh mesh);
float	*merge_coordinates(t_vec3 vertices[], float texture[], unsigned int l_ver, unsigned int l_tex);

#endif
