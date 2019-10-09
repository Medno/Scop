/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_constructors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:01:03 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:01:04 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_new(enum e_mat type)
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

t_mat4	mat4_copy(t_mat4 copy)
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


t_mat4			mat4_add_vec3(t_mat4 mat, t_vec3 vect, uint8_t coord)
{
	mat.matrix[coord][0] = vect.x;
	mat.matrix[coord][1] = vect.y;
	mat.matrix[coord][2] = vect.z;
	return (mat);
}

void	mat4_print(t_mat4 m)
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
