#include "get_next_line.h"
#include <unistd.h>

int main(){
    char **line;
	int res;
    int fd;

	fd = open("kimetsu.txt", O_RDONLY);
	/* fd = open("empty.txt", O_RDONLY); */
	/* fd = 1; */
	line = (char**)malloc(sizeof(char*));

	while (1){
		res = get_next_line(fd, line);
		printf("res = %d\n", res);
		if (res == -1)
			break;
		printf("############# <%s>\n", *line);
		free(*line);
		if (res == 0)
			break;
	}
	//printf("%d\n" ,get_next_line(fd, &line));// 1
    /* printf("%s\n",&line);// tanjiro */
    /* printf("%d\n",get_next_line(fd, &line));// 1 */
    /* printf("%s\n",&line);// nezuko */
    /* printf("%d\n",get_next_line(fd, &line));// 0 */
    /* printf("%s\n",&line);// zennitsu */
    close(fd);

	system("leaks a.out");

	return (0);
}
