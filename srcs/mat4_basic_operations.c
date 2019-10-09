/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_basic_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:59:58 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:00:14 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat4.h"

t_mat4	mat4_add(t_mat4 first, t_mat4 second)
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

t_mat4	mat4_mul(t_mat4 first, t_mat4 second)
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
