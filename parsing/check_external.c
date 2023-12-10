/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_external.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:15:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/08 19:23:13 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_first(char **dtr, int i)
{
	if (!((dtr[i]) && ((dtr[i][0] == 'N' && dtr[i][1] == 'O')
		|| (dtr[i][0] == 'W' && dtr[i][1] == 'E') || ((dtr[i][0] == 'S'
		&& dtr[i][1] == 'O')) || ((dtr[i][0] == 'E'
		&& dtr[i][1] == 'A')) || ((dtr[i][0] == 'C'))
		|| ((dtr[i][0] == 'F')))))
	{
		printf("Check Textures and Rgb's\n");
		exit(2);
	}
}

int	check_ele(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ')
		return (1);
	return (0);
}

void	check_trimmed_map(char **dtr, int i)
{
	int	j;

	j = 0;
	while (dtr[i])
	{
		j = 0;
		while (dtr[i][j])
		{
			if (check_ele(dtr[i][j]))
			{
				printf("check map elements\n");
				exit(2);
			}
			j++;
		}
		free(dtr[i]);
		i++;
	}
	free(dtr);
}

void	trim_check(char *str)
{
	int		i;
	char	**dtr;
	char	*tmp;

	dtr = ft_split(str, '\n');
	free(str);
	i = 0;
	while (dtr[i] && dtr[i][0] != '1')
	{
		tmp = dtr[i];
		dtr[i] = ft_strtrim(dtr[i], " ");
		free(tmp);
		check_first(dtr, i);
		free(dtr[i]);
		i++;
	}
	check_trimmed_map(dtr, i);
}

void	check_external(char **strs, int len)
{
	int		size;
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	size = 0;
	while (i < len)
	{
		size += ft_strlen(strs[i]);
		i++;
	}
	str = malloc(size + 1);
	i = 0;
	while (i < len)
	{
		tmp = str;
		str = ft_strjoin(str, strs[i]);
		free(tmp);
		i++;
	}
	trim_check(str);
}
