#include "get_next_line.h"
#include <unistd.h>

int main(){
    char *line;
    int fd = open("kimetsu.txt",O_RDONLY);

    printf("%d\n" ,get_next_line(fd, &line));// 1
    /* printf("%s\n",&line);// tanjiro */
    /* printf("%d\n",get_next_line(fd, &line));// 1 */
    /* printf("%s\n",&line);// nezuko */
    /* printf("%d\n",get_next_line(fd, &line));// 0 */
    /* printf("%s\n",&line);// zennitsu */
    close(fd);
}
