#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int get_next_line(int fd, char **line);
int check_sbuff_newline(char **sbuff, char **line);
int check_buff_newline(char *buff, char **sbuff, char **line);
int move_sbuff(char **sbuff, char **line, int res_read);
int move_buff(char **buff, char **sbuff);
char *ft_slice(char *s, int start_index, int len);
int free_two(char **buff, char ***sbuff, int n);
int init_buff(char **buff, char ***sbuff, size_t len, int flag);
char *ft_concat(char *s1, char *s2);
