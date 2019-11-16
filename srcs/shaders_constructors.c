/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:29:48 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 19:06:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shaders.h"

static uint8_t	check_shader_error(GLuint shad, GLuint f, uint8_t p, char *err)
{
	GLint	success;
	GLchar	error[1024];

	if (p)
		glGetProgramiv(shad, f, &success);
	else
		glGetShaderiv(shad, f, &success);
	if (success == GL_FALSE)
	{
		if (p)
			glGetProgramInfoLog(shad, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shad, sizeof(error), NULL, error);
		dprintf(2, "%s%s\n", err, error);
		return (1);
	}
	return (0);
}

static uint8_t	create_shader(const char *file, GLenum shader_type)
{
	char			*full_path;
	const GLchar	*shader_src_str[1];
	GLuint			shader;
	GLint			len_shader_src_str[1];

	full_path = (shader_type == GL_VERTEX_SHADER)
	? ft_strjoin(file, ".vert") : ft_strjoin(file, ".frag");
	if (!full_path)
		return (0);
	shader_src_str[0] = (GLchar *)read_file(full_path, "r", NULL);
	ft_strdel(&full_path);
	if (!shader_src_str[0])
		return (0);
	shader = glCreateShader(shader_type);
	len_shader_src_str[0] = strlen(shader_src_str[0]);
	glShaderSource(shader, 1, shader_src_str, len_shader_src_str);
	glCompileShader(shader);
	ft_strdel((char **)&shader_src_str[0]);
	if (check_shader_error(shader, GL_COMPILE_STATUS, 0,
		"Error: Shader compilation failed: "))
		return (0);
	return (shader);
}

static void		find_uniforms(t_shader *shader)
{
	shader->uniforms[MODEL_U] =
		glGetUniformLocation(shader->program, "model");
	shader->uniforms[VIEW_U] =
		glGetUniformLocation(shader->program, "view");
	shader->uniforms[PROJECTION_U] =
		glGetUniformLocation(shader->program, "projection");
	shader->uniforms[ALPHA_U] =
		glGetUniformLocation(shader->program, "aAlphaTex");
	shader->uniforms[LIGHT_COLOR_U] =
		glGetUniformLocation(shader->program, "lightColor");
	shader->uniforms[LIGHT_POS_U] =
		glGetUniformLocation(shader->program, "lightPos");
	shader->uniforms[CAMERA_POS_U] =
		glGetUniformLocation(shader->program, "viewPos");
	shader->uniforms[ENABLE_LIGHT_U] =
		glGetUniformLocation(shader->program, "enableLight");
	shader->uniforms[COLORS_MODE_U] =
		glGetUniformLocation(shader->program, "colorMode");
}

/*
** Construction, compilation and linking of vertex and fragment shader
** Linking the uniforms matrices corresponding to their utility
**   file	- File name of the shader
**  shader	- Structure where we store the location of uniform matrices
**			  and id of shader objects
*/

t_shader		*construct_shader(const char *file)
{
	int			i;
	t_shader	*shader;

	i = 0;
	if (!(shader = (t_shader *)malloc(sizeof(t_shader))))
		return (NULL);
	shader->id_so[0] = create_shader(file, GL_VERTEX_SHADER);
	shader->id_so[1] = create_shader(file, GL_FRAGMENT_SHADER);
	if (!shader->id_so[0] || !shader->id_so[1])
		return (delete_shader(shader));
	shader->program = glCreateProgram();
	while (i < NUM_SHADERS)
	{
		glAttachShader(shader->program, shader->id_so[i]);
		i++;
	}
	glLinkProgram(shader->program);
	if (check_shader_error(shader->program, GL_LINK_STATUS, 1,
		"Error: Program linking failed: "))
		return (delete_shader(shader));
	find_uniforms(shader);
	return (shader);
}

t_shader		*delete_shader(t_shader *shader)
{
	int	i;

	i = 0;
	while (i < NUM_SHADERS)
	{
		if (shader->id_so[i] != 0)
		{
			glDetachShader(shader->program, shader->id_so[i]);
			glDeleteShader(shader->id_so[i]);
		}
		i++;
	}
	if (shader->program)
		glDeleteProgram(shader->program);
	free(shader);
	return (NULL);
}
