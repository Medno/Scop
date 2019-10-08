/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:29:48 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 11:19:03 by pchadeni         ###   ########.fr       */
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
	shader_src_str[0] = read_shader_file(full_path);
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

uint8_t			construct_shader(const char *file, t_shader *shader)
{
	int	i;

	i = 0;
	shader->shaders[0] = create_shader(file, GL_VERTEX_SHADER);
	shader->shaders[1] = create_shader(file, GL_FRAGMENT_SHADER);
	if (!shader->shaders[0] || !shader->shaders[1])
		return (0);
	shader->program = glCreateProgram();
	while (i < NUM_SHADERS)
	{
		glAttachShader(shader->program, shader->shaders[i]);
		i++;
	}
	glLinkProgram(shader->program);
	if (check_shader_error(shader->program, GL_LINK_STATUS, 1,
		"Error: Program linking failed: "))
		return (0);
	shader->uniforms[MODEL_U] =
		glGetUniformLocation(shader->program, "model");
	shader->uniforms[VIEW_U] =
		glGetUniformLocation(shader->program, "view");
	shader->uniforms[PROJECTION_U] =
		glGetUniformLocation(shader->program, "projection");
	return (1);
}

void			delete_shader(t_shader shader)
{
	int	i;

	i = 0;
	while (i < NUM_SHADERS)
	{
		glDetachShader(shader.program, shader.shaders[i]);
		glDeleteShader(shader.shaders[i]);
		i++;
	}
	glDeleteProgram(shader.program);
}

void			use_shader(t_shader shader)
{
	glUseProgram(shader.program);
}

/*
** Send matrices (MVP) to the vertex shader
*/

void			update_shader(t_shader s, t_transform t)
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;

	model = get_model(t);
	glUniformMatrix4fv(
			s.uniforms[MODEL_U], 1, GL_TRUE, &model.matrix[0][0]);
	view = new_mat4(IDENTITY);
	view = translate(view, create_vec3(0.0f, 0.0f, -3.0f));
	glUniformMatrix4fv(
			s.uniforms[VIEW_U], 1, GL_TRUE, &view.matrix[0][0]);
	projection = projection_mat4(45.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 100.0f);
	glUniformMatrix4fv(
			s.uniforms[PROJECTION_U], 1, GL_TRUE, &projection.matrix[0][0]);
}
