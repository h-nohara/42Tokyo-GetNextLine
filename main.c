#include "get_next_line.h"
#include <unistd.h>

int main(){
    char **line;
	int res;
    int fd;

	fd = open("kimetsu.txt", O_RDONLY);

	while (1){
		res = get_next_line(fd, line);
		printf("res = %d\n", res);
		if (res == -1)
			break;
		printf("<%s>\n", *line);
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

	return (0);
}
