#include "parser.h"



uint8_t	check_float(const char *str, float f)
{
	size_t	len;
	size_t	i;
	uint8_t	point;
	uint8_t	is_digit;

	i = 0;
	point = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		is_digit = ft_isdigit(str[i]);
		if (!point && str[i] == '.' && i != 0)
			point = 1;
		else if (str[i] == '.' && point)
			return (0);
		else if (!is_digit)
			return (0);
		i++;
	}
	if (!point)
		return (0);
	f = strtod(str);
	if (errno == ERANGE)
		return (0);
	return (1);
}

void	parse_obj_file(const char *obj_name)
{
	char	*obj_data_str;
	char	**obj_data;

	if (!(obj_data_str = read_file(obj_name, "r")))
		return ;
	if ((obj_data = ft_strsplit(obj_data_str, '\n')) != NULL)
	{
		
		ft_tabdel(obj_data);
	}
	ft_strdel(&obj_data_str);
	return ;
}
