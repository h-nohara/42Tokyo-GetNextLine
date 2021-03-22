#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int get_next_line(int fd, char **line);
int check_sbuff_newline(char *buff, char **sbuff, char **line);
int check_buff_newline(char *buff, char **sbuff, char **line);
int move_sbuff(char *buff, char **sbuff, char **line, int res_read);
int move_buff(char **buff, char **sbuff);
char *ft_slice(char *s, int start_index, int len);
int free_two(char *buff, char **static_buff, int n);
void init_buff(char *buff, unsigned int len);
char *ft_concat(char *s1, char *s2);
