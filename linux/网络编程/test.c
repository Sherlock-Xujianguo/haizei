#include <stdio.h>
#include <string.h>

struct message {
    char from[20];
    int flag;
    char message[1024];
};

int main()
{
    struct message m;
    strcpy(m.from, "夏洛克徐建国");
    m.flag = 100;
    strcpy(m.message, "hello");
    
    char *temp = (char *)&m;
    printf("%s\n", temp);
    struct message *a = (struct message *)temp;
    printf("%s\n", a -> from);
    printf("%d\n", a -> flag);
    printf("%s\n", a -> message);
    return 0;
}

