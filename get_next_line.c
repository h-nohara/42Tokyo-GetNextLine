#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	char *buff;
	static char **static_buff;
	int i;
	char *tmp_s;

	while (1)
	{
		init_buff(buff, BUFFER_SIZE); /* static_buffはサイズは実際に格納するサイズに合わせる*/
		if (!buff)
			return (-1);
		if (static_buff && *static_buff) /* static_buffに改行があった場合：readせずに終了 */
		{
			i = 0;
			while ((*static_buff)[i])
			{
				if ((*static_buff)[i] == '\n')
				{
					*line = ft_slice(*static_buff, 0, i + 1); /* *lineに代入する前にfreeしなくて大丈夫？ */
					if (!(*line))
						return (free_two(buff, static_buff, -1));
					tmp_s = ft_slice(*static_buff, i + 1, -1);
					free(*static_buff);
					*static_buff = tmp_s;
					return (1);
				}
			}
		}
		res = read(fd, buff, BUFFER_SIZE);
		if (res == 0 || res == -1)
		{
			/* static_buffを取り出してから終了 */
			if (static_buff && *static_buff)
			{
				if (!(*line = ft_slice(*static_buff, 0, -1)))
					res = -1;
			}
			return (free_two(buff, static_buff, res));
		}
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
			{
				/* buffの改行までを切り出し */
				tmp_s = ft_slice(buff, 0, i + 1);
				if (!tmp_s)
					return (free_two(buff, static_buff, -1));
				if (static_buff && *static_buff)
				{   /* static_buffが存在したら、(static_buff + buffの頭)を*lineに代入 */
					*line = ft_concat(static_buff, tmp_s);
					free(tmp_s);
				} else {
					*line = tmp_s;
				}
				if (!(*line))
					return (free_two(buff, static_buff, -1));
				/* buffの尾をstatic_buffに代入 */
				free(*static_buff);
				*static_buff = ft_slice(buff, i + 1, -1);
				free(buff);
				if (!(*static_buff))
					return (-1);
				return (1);
			}
		}
		/* もし改行がなかったら：static_buffにbuffを移す（もしstatic_buffが存在してたら結合してから移す) */
		if (static_buff && *static_buff)
		{

		}
		else
			*static_buff = ft_slice(buff, 0, -1);
	}
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
	return (res);
}

/* sをcでhead/tailに分割、headを返してdest_tailにtailを代入 */
char *ft_split(char *s, char c, char **dest_tail)
{
	int i;
	int j;
	char *head;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	head = (char*)malloc(sizeof(char) * (i + 1));
	if (!head)
		return (NULL);
	j = 0;
	while (j < i)
	{
		head[j] = s[j];
		++j;
	}
	head[i] = '\0';
	++i;
	j = 0;
	while (s[i]) /* dest_tailがヌル埋めされていることが前提 */
		(*dest_tail)[j++] = s[i++];
	return (head);
}

size_t strlen(char *s)
{
	int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int free_two(char *buff, char **static_buff, int n)
{
	free(buff);
	if (static_buff)
	{
		if (*static_buff)
			free(*static_buff);
		free(static_buff);
	}
	return (n);
}

int get_next_line(int fd, char **line)
{
	static char *buff = init_buff();
	char *static_buff;
	int res;
	int i;

	if (!buff)
		return (-1);
	if (buff[0] == '\0')
		res = read(fd, buff, BUFFER_SIZE); /* buffが空ならまず代入 */
	if (res == -1)
	{
		free(buff);
		return (-1);
	}
	static_buff = NULL;
	i = 0;
	while (1)
	{
		if (find_newline(buff, static_buff, line, &i) == 1)
		{
			free(static_buff);
			return (1);
		}
		/* 以下は改行がなかったとき*/
		if (!static_buff)
		{
			static_buff = ft_slice(buf, ft_strlen(buf));
			if (!static_buff)
			{
				free(buff);
				return (-1);
			}
		}
		else
		{
			static_buff = ft_concat(static_buff, ft_slice(buff, ft_strlen(buff))); // to free old static_buff
		}
		if (res == 0)
		{
			*line = ft_slice(static_buff, ft_strlen(static_buff));
			return (0);
		}
		res = read(fd, buff, BUFFER_SIZE);
		if (res == -1)
			return (-1);
	}
	return (0);
}

void *init_buff(char *buff, unsigned int len)
{
	unsigned int size;
	int i;

	size = len + 1;
	if (!buff)
	{
		buff = (char*)malloc(sizeof(char) * size);
		if (!buff)
			return (NULL);
	}
	i = 0;
	while (i < size)
		buff[i++] = '\0';
}

int find_newline(char *buff, char *static_buff, char **line, int *index)
{
	char *tmp_s;

	while (buff[*index])
	{
		if (buff[*index] == '\n')
			{
				*tmp_s = ft_slice(buff, '\n'); /* 先頭から長さ分だけコピー(malloc) */
				if (!tmp_s)
					return -1;
				if (!static_buff)
					*line = tmp_s;
				else
					*line = ft_concat(static_buff, tmp_s);
				if (!(*line))
					return -1;
				ft_slide_buff(buff, buff + *index + 1); /* 左にスライドして、先頭から始まるように、後ろはヌルパディング */
				return (1);
			}
		++(*index);
	}
	return (0);
}

char *_ft_slice(char *buff, char c)
{
	char *res;
	int len;
	int i;

	len = 0;
	while ((buff[len] != c) && buff[len])
		++len;
	res = (char*)malloc(sizeof(char) * (len + 1));
	if (!res)
		return NULL
	i = 0;
	while (i < len)
		res[i++] = buff[i];
	res[len] = '\0';
	return res;
}

char *ft_concat(char *s1, char *s2)
{
	char *res;
	int i;
	int j;

	i = 0;
	while (*s1)
		i++;
	while (*s2)
		i++;
	res = (char*)malloc(sizeof(char) * (i + 1));
	if (!res)
		return NULL;
	i = 0;
	j = 0;
	while (*s1)
		res[j++] = s1[i++];
	i = 0;
	while (*s2)
		res[j++] = s2[i++];
	res[j] = '\0';
	return res;
}

void ft_slide_buff(char *s, int start_index)
{
	int i;

	i = 0;
	while (i < start_index)
		s[i++] = 0;
	i = 0;
	while (s[start_index])
	{
		s[i] = s[start_index];
		s[start_index] = 0;
		start_index++;
		i++;
	}
}
