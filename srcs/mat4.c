/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:15:57 by pchadeni          #+#    #+#             */
/*   Updated: 2019/09/30 17:20:41 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	add_mat4(t_mat4 first, t_mat4 second)
{
	t_mat4	res;
	int		i;

	i = 0;
	while (i < 4)
	{
		res.matrix[i][0] = first.matrix[i][0] + second.matrix[i][0];
		res.matrix[i][1] = first.matrix[i][1] + second.matrix[i][1];
		res.matrix[i][2] = first.matrix[i][2] + second.matrix[i][2];
		res.matrix[i][3] = first.matrix[i][3] + second.matrix[i][3];
		i++;
	}
	return (res);
}

t_mat4	mul_mat4(t_mat4 first, t_mat4 second)
{
	t_mat4	res;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.matrix[i][j] = first.matrix[i][0] * second.matrix[0][j]
				+ first.matrix[i][1] * second.matrix[1][j]
				+ first.matrix[i][2] * second.matrix[2][j]
				+ first.matrix[i][3] * second.matrix[3][j];
			j++;
		}
		i++;
	}
	return (res);
}

t_mat4	new_mat4(enum e_mat type)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.matrix[i][j] = (type == IDENTITY && i == j) ? 1 : 0;
			j++;
		}
		i++;
	}
	return (result);
}

t_mat4	projection_mat4(float angle, float ratio, float near, float far)
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

t_mat4	copy_mat4(t_mat4 copy)
{
	t_mat4	result;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.matrix[i][j] = copy.matrix[i][j];
			j++;
		}
		i++;
	}
	return (result);
}

t_mat4	translate(t_mat4 mat4, t_vec3 vec3)
{
	t_mat4	result;

	result = copy_mat4(mat4);
	result.matrix[0][3] = (mat4.matrix[0][0] + mat4.matrix[0][1]
			+ mat4.matrix[0][2]) * vec3.x;
	result.matrix[1][3] = (mat4.matrix[1][0] + mat4.matrix[1][1]
			+ mat4.matrix[1][2]) * vec3.y;
	result.matrix[2][3] = (mat4.matrix[2][0] + mat4.matrix[2][1]
		+ mat4.matrix[2][2]) * vec3.z;
	return (result);
}

void	print_mat4(t_mat4 m)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dprintf(2, "%f ", m.matrix[i][j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
}
