/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 19:25:08 by pchadeni          #+#    #+#             */
/*   Updated: 2019/10/08 19:26:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "logger.h"
#include "vec3.h"

float	*merge_coordinates(t_vec3 vertices[], float texture[],
		unsigned int l_ver, unsigned int l_tex)
{
	float	*merged;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	if (!(merged = (float *)malloc(sizeof(float) * l_ver * l_tex * 3)))
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (k < l_ver)
	{
		merged[i] = vertices[k].x;
		merged[i + 1] = vertices[k].y;
		merged[i + 2] = vertices[k].z;
		merged[i + 3] = texture[j];
		merged[i + 4] = texture[j + 1];
		i += 5;
		j += 2;
		k += 1;
	}
	return (merged);
}
