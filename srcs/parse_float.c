/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:27:15 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 12:00:45 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	check_float(const char *str, float *f)
{
	size_t	len;
	size_t	i;
	uint8_t	point;
	uint8_t	is_digit;
	char	*bad;

	i = 0;
	point = 0;
	len = ft_strlen(str);
	*f = 0.0;
	while (i < len && !ft_iswsp(str[i]))
	{
		is_digit = ft_isdigit(str[i]);
		if (!point && str[i] == '.' && i != 0 && i != len - 1)
			point = 1;
		else if ((str[i] == '.' && point) || (!is_digit && str[i] != '-')
			|| (str[i] == '-'  && i != 0))
			return (0);
		i++;
	}
	if (!point)
		return (0);
	*f = strtof(str, &bad);
	if (*f == 0.0 && bad == str)
		return (0);
	return (1);
}
