#include "get_next_line.h"

char *ft_concat(char *s1, char *s2)
{
	char *res;
	int i;
	int j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j++])
		i++;
	res = (char*)malloc(sizeof(char) * (i + 1));
	if (!res)
		return NULL;
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
 	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return res;
}

char *ft_slice(char *s, int start_index, int len)
{
	int i;
	char *res;

	if (len == -1)
	{
		len = 0;
		while (s[start_index + len])
			++len;
	}
	res = (char*)malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start_index + i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

int free_two(char **buff, char ***static_buff, int n)
{
	if (*buff)
		free(*buff);
	if (*static_buff && n != 1)
	{
		if (**static_buff)
			free(**static_buff);
		free(*static_buff);
	}
	return (n);
}

int init_buff(char **buff, char ***sbuff, size_t len, int flag)
{
	unsigned int size;
	size_t i;

	size = len + 1;
	if (flag == 1)
	{
		*buff = (char*)malloc(sizeof(char) * size);
		if (!(*buff))
			return (-1);
	}
	i = 0;
	while (i < size)
		(*buff)[i++] = '\0';
	if (flag == 1 && *sbuff == NULL)
	{
		*sbuff = (char**)malloc(sizeof(char*));
		if (!(*sbuff))
			return (-1);
		**sbuff = (char*)malloc(sizeof(char) * 1);
		if (!(**sbuff))
			return (-1);
		(**sbuff)[0] = '\0';
	}
	return (0);
}
