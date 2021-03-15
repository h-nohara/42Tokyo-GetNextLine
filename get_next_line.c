#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	static char *buff = init_buff();
	char *tmp_buff;
	int res;
	int i;
	int found;

	if (!buff)
		return (-1);
	if (buff[0] == '\0')
		res = read(fd, buff, BUFFER_SIZE); /* buffが空ならまず代入 */
	if (res == -1)
	{
		free(buff);
		return (-1);
	}
	tmp_buff = NULL;
	i = 0;
	while (1)
	{
		found = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
			{
				found = 1;
				if (!tmp_buff)
					*line = ft_slice(buff, i); /* 先頭から長さ分だけコピー(malloc) */
				else
					*line = ft_concat(tmp_buff, ft_slice(buff, i));
				ft_slide_buff(buff, buff + i + 1); /* 左にスライドして、先頭から始まるように、後ろはヌルパディング */
				break ;
			}
			++i;
		}
		if (found)
			return (1);
		/* 以下は改行がなかったとき*/
		if (!tmp_buff)
		{
			tmp_buff = ft_slice(buf, ft_strlen(buf));
			if (!tmp_buff)
			{
				free(buff);
				return (-1);
			}
		}
		else
		{
			tmp_buff = ft_concat(tmp_buff, ft_slice(buff, ft_strlen(buff))); // to free old tmp_buff
		}
		if (res == 0)
		{
			*line = ft_slice(tmp_buff, ft_strlen(tmp_buff));
			return (0);
		}
		res = read(fd, buff, BUFFER_SIZE);
		if (res == -1)
			return (-1);
	}
	return (0);
}

char *init_buff(void)
{
	char *buff;
	int size;
	int i;

	size = BUFFER_SIZE + 1;
	buff = (char*)malloc(sizeof(char) * size);
	if (!buff)
		return (NULL);
	i = 0;
	while (i < size)
		buff[i++] = '\0';
	return (buff);
}
