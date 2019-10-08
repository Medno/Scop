/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_transformations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:08:05 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:13:06 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "model.h"

t_mat4			translate(t_mat4 mat4, t_vec3 vec3)
{
	t_mat4	result;

	result = mat4;
	result.matrix[0][3] = (mat4.matrix[0][0] + mat4.matrix[0][1]
			+ mat4.matrix[0][2]) * vec3.x;
	result.matrix[1][3] = (mat4.matrix[1][0] + mat4.matrix[1][1]
			+ mat4.matrix[1][2]) * vec3.y;
	result.matrix[2][3] = (mat4.matrix[2][0] + mat4.matrix[2][1]
		+ mat4.matrix[2][2]) * vec3.z;
	return (result);
}

t_mat4			projection_mat4(float angle, float ratio,
		float near, float far)
{
	t_mat4	result;
	float	tan_half_angle;

	result = new_mat4(ZEROS);
	tan_half_angle = tan(angle / 2);
	result.matrix[0][0] = 1 / (ratio * tan_half_angle);
	result.matrix[1][1] = 1 / (tan_half_angle);
	result.matrix[2][2] = -(far + near) / (far - near);
	result.matrix[3][2] = -1;
	result.matrix[2][3] = -(2 * far * near) / (far - near);
	return (result);
}

t_mat4			scale(t_transform t)
{
	t_mat4	scaled;

	scaled = new_mat4(IDENTITY);
	scaled.matrix[0][0] *= t.scale.x;
	scaled.matrix[1][1] *= t.scale.y;
	scaled.matrix[2][2] *= t.scale.z;
	return (scaled);
}

static t_mat4	rotate_axis(t_transform t, enum e_axis axis)
{
	t_mat4	n_mat4;
	int		i;
	int		j;
	float	angle;

	n_mat4 = new_mat4(IDENTITY);
	i = (axis == X_AXIS) ? 1 : 0;
	j = (axis == Y_AXIS) ? i + 2 : i + 1;
	if (axis == X_AXIS)
		angle = t.rotation.x;
	else if (axis == Y_AXIS)
		angle = t.rotation.y;
	else
		angle = t.rotation.z;
	n_mat4.matrix[i][i] = cosf(angle);
	n_mat4.matrix[i][j] = (axis == Y_AXIS) ? sinf(angle) : -sinf(angle);
	n_mat4.matrix[j][i] = (axis == Y_AXIS) ? -sinf(angle) : sinf(angle);
	i = j;
	n_mat4.matrix[i][i] = cosf(angle);
	return (n_mat4);
}

t_mat4			rotate(t_transform t)
{
	t_mat4	rot_x_matrix;
	t_mat4	rot_y_matrix;
	t_mat4	rot_z_matrix;

	rot_x_matrix = rotate_axis(t, X_AXIS);
	rot_y_matrix = rotate_axis(t, Y_AXIS);
	rot_z_matrix = rotate_axis(t, Z_AXIS);
	return (mul_mat4(rot_x_matrix, mul_mat4(rot_y_matrix, rot_z_matrix)));
}
