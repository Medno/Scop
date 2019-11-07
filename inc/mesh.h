/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 15:43:20 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 15:45:53 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# define GL_SILENCE_DEPRECATION
# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

# include "vec3.h"
# include "handle_error.h"
# include "textures.h"
# include "parser.h"

enum
{
	POSITION_VB,

	NUM_BUFFERS
};

typedef struct	s_mesh
{
	GLuint			vao;
	GLuint			vbo[NUM_BUFFERS];
	unsigned int	count_draw;
	unsigned int	texture;
	unsigned int	len_textures;
}				t_mesh;

uint8_t			create_mesh(const char *filename, t_mesh *mesh);
void			delete_mesh(t_mesh mesh);
void			draw_mesh(t_mesh mesh);
float			*merge_coordinates(t_vec3 vertices[], float texture[],
		unsigned int l_ver, unsigned int l_tex);

#endif
