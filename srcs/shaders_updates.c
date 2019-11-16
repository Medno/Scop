/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders_updates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:51:43 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 11:41:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"

void	use_shader(t_shader *shader)
{
	glUseProgram(shader->program);
}

/*
** Send matrices (MVP) to the vertex shader
*/

void	update_shader_mvp(t_shader *shader, t_transform *trans, t_camera *cam)
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;
	float	ratio;

	model = get_model(*trans);
	glUniformMatrix4fv(
			shader->uniforms[MODEL_U], 1, GL_TRUE, &model.matrix[0][0]);
	view = view_look_at(cam->position,
		vec3_add(cam->position, cam->front), cam->up);
	glUniformMatrix4fv(shader->uniforms[VIEW_U], 1, GL_TRUE,
			&view.matrix[0][0]);
	ratio = (float)WIDTH / (float)HEIGHT;
	projection = projection_mat4(
			degree_to_radian(cam->fov), ratio, 0.01f, 100.0f);
	glUniformMatrix4fv(shader->uniforms[PROJECTION_U], 1, GL_TRUE,
			&projection.matrix[0][0]);
}

void	update_obj_shader(t_monitor *m)
{
	update_shader_mvp(m->obj_shader, m->transformation, m->camera);
	if (m->enable_texture && m->obj_shader->alpha < 1.0)
		m->obj_shader->alpha += 0.001;
	else if (!m->enable_texture && m->obj_shader->alpha > 0.0)
		m->obj_shader->alpha -= 0.001;
	glUniform1f(m->obj_shader->uniforms[ALPHA_U], m->obj_shader->alpha);
}

void	set_light_uniforms(t_shader *shader)
{
(void)shader;
}

void	update_light_shader(t_monitor *m)
{
	update_shader_mvp(m->light_shader, m->light_trans, m->camera);

}
