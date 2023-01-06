/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarchal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:36:38 by gmarchal          #+#    #+#             */
/*   Updated: 2023/01/06 15:11:04 by gmarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_line(char *my_buffer, int *check, char *my_static)
{
	char	*my_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	my_line = malloc (sizeof(char) * (ft_strlen(my_buffer) + 1));
	if (!my_line)
		return (0);
	while (my_buffer[i] && *check != 1)
	{
		if (my_buffer[i] == '\n')
			*check = 1;
		my_line[i] = my_buffer[i];
		i++;
	}
	my_line[i] = '\0';
	if (i == 0)
		*check = 1;
	while (my_buffer[i])
		my_static[j++] = my_buffer[i++];
	my_static[j] = '\0';
	return (my_line);
}

char	*get_next_line(int fd)
{
	static char	my_static[BUFFER_SIZE + 1];
	int			check;
	char		*my_line;
	char		my_buffer[BUFFER_SIZE + 1];
	char		*tmp;

	check = 0;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (0);
	my_line = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!my_line)
		return (0);
	tmp = ft_strdup_mod(my_static, &check);
	if (!tmp)
		return (0);
	while (check == 0)
	{
		ft_bzero(my_buffer, BUFFER_SIZE + 1);
		read(fd, my_buffer, BUFFER_SIZE);
		// proteger read
		my_line = ft_line(my_buffer, &check, my_static);
		tmp = ft_strjoin(tmp, my_line);
	}
	if (!tmp[0])
		return (0);
	return (tmp);
}

#include <fcntl.h> // delete (pour open)
#include <stdio.h> // delete
int	main(void)
{
	int		fd;
	char	*ligne;

	fd = open("test_file", O_RDONLY);
	ligne = get_next_line(fd);
	while (ligne)
	{
		printf("%s", ligne);
		free(ligne);
		ligne = get_next_line(fd);
	}
	free(ligne);
	system("leaks a.out");
	return (0);
}
