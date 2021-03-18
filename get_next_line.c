#include "get_next_line.h"

int get_next_line(int fd, char **line)
{
	char *buff;
	static char **static_buff;
	int res;

	while (1)
	{
		init_buff(buff, BUFFER_SIZE); /* static_buffはサイズは実際に格納するサイズに合わせる*/
		if (!buff)
			return (-1);

		/* static_buffに改行があった場合：readせずに終了 */
		res = check_sbuff_newline(buff, static_buff, line);
		if (res != 1)
			return (res);

		res = read(fd, buff, BUFFER_SIZE);

		/* static_buffを取り出してから終了 */
		if (res == 0 || res == -1)
			return (move_sbuff(buff, static_buff, line, res));

		res = check_buff_newline(buff, static_buff, line);
		if (res != 0)
			return (res);

		if (move_buff(buff, static_buff) == -1)
			return (-1);
	}
	return (-1);
}

int check_sbuff_newline(char *buff, char **sbuff, char **line)
{
	int i;
	char *s;

	if (sbuff && *sbuff) /* static_buffに改行があった場合：readせずに終了 */
	{
		i = 0;
		while ((*sbuff)[i])
		{
			if ((*sbuff)[i] == '\n')
			{
				*line = ft_slice(*sbuff, 0, i); /* *lineに代入する前にfreeしなくて大丈夫？ */
				if (!(*line))
					return (free_two(buff, sbuff, -1));
				s = ft_slice(*sbuff, i + 1, -1);
				if (!s)
					return (free_two(buff, sbuff, -1));
				free(*sbuff);
				*sbuff = s;
				return (1);
			}
		}
	}
	return (0);
}

int check_buff_newline(char *buff, char **sbuff, char **line)
{
	int i;
	char *tmp_s;

	i = 0;
	while (buff[i] && (buff[i] != '\n'))
		++i;
	if (buff[i] != '\n')
		return (0);
	/* buffの改行までを切り出し */
	tmp_s = ft_slice(buff, 0, i);
	if (!tmp_s)
		return (free_two(buff, sbuff, -1));
	if (sbuff && *sbuff)
	{   /* static_buffが存在したら、(static_buff + buffの頭)を*lineに代入 */
		*line = ft_concat(*sbuff, tmp_s);
		free(tmp_s);
		if (!(*line))
			return (free_two(buff, sbuff, -1));
	}
	else
		*line = tmp_s;
	/* buffの尾をstatic_buffに代入 */
	free(*sbuff);
	*sbuff = ft_slice(buff, i + 1, -1);
	free(buff);
	if (!(*sbuff))
		return (-1);
	return (1);
}

int move_sbuff(char *buff, char **sbuff, char **line, int res_read)
{
	if (sbuff && *sbuff)
	{
		if (res_read == 0)
		{
			if (!(*line = ft_slice(*sbuff, 0, -1)))
				res_read = -1;
		}
	}
	return (free_two(buff, sbuff, res_read));
}

int move_buff(char *buff, char **sbuff)
{
	char *tmp_s;

	/* もし改行がなかったら：static_buffにbuffを移す（もしstatic_buffが存在してたら結合してから移す) */
	if (sbuff && *sbuff)
	{
		tmp_s = ft_concat(*sbuff, buff);
		if (!tmp_s)
			return free_two(buff, sbuff, -1);
		free(buff);
		*sbuff = tmp_s;
	}
	else
	{
		if (!(*sbuff = ft_slice(buff, 0, -1)))
			return free_two(buff, sbuff, -1);
	}
	return (0);
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


void init_buff(char *buff, unsigned int len)
{
	unsigned int size;
	int i;

	size = len + 1;
	if (!buff)
	{
		buff = (char*)malloc(sizeof(char) * size);
		if (!buff)
			return ;
	}
	i = 0;
	while (i < size)
		buff[i++] = '\0';
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
