/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:27:15 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/05 18:30:57 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	check_float(const char *str, float *f)
{
	size_t	len;
	size_t	i;
	uint8_t	point;
	uint8_t	is_digit;

	i = 0;
	point = 0;
	len = ft_strlen(str);
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
	errno = 0;
	*f = strtof(str, NULL);
	if (errno == ERANGE)
		return (0);
	return (1);
}

/*
int	float_parser_main()
{
	char	*tests[] = {
		"1.0", "2.", "2.0402095308520457248082",
		"55555555555555555555555555555555555555",
		"55555555555555555555555555555555555555333333333333333333333333333.0",
		"55555555555555555555555555555555555555.0",
		"abc", "a.0", "1a.0", "1.a0",
		"1..0", ".10", "2.2.4", "1.3f", "1.4 ", "2",
		"-2", "-2.0"
	};
	size_t	len = sizeof(tests) / sizeof(tests[0]);
	uint8_t	isfloat;
	float	fl;

	for (size_t i = 0; i < len; i++) {
		printf("Test for : |%s|\n", tests[i]);
		isfloat = check_float(tests[i], &fl);
		if (isfloat)
			printf("Is a float\n");
		else
			printf("Is not a float\n");
	}
	return (0);
}
*/
