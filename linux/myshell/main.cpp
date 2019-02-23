#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h> //获取拥有者
#include <grp.h> //获取所属组
#include <sys/stat.h> //获取文件权限
#include <time.h>
using namespace std;
char path[1000];
char user[] = "[sx shell]";
void hello()
{
    printf("%s", user);
    printf("%s", path);
    printf("# ");
    return ;
}
void rwx(int mode, char *zt) {
    if (S_ISDIR(mode)) zt[0] = 'd';
    if (S_ISCHR(mode)) zt[0] = 'c';
    if (S_ISBLK(mode)) zt[0] = 'b';
    if ((mode & S_IRUSR)) zt[1] = 'r';
    if ((mode & S_IWUSR)) zt[2] = 'w';
    if ((mode & S_IXUSR)) zt[3] = 'x';
    if ((mode & S_IRGRP)) zt[4] = 'r';
    if ((mode & S_IWGRP)) zt[5] = 'w';
    if ((mode & S_IXGRP)) zt[6] = 'x';
    if ((mode & S_IROTH)) zt[7] = 'r';
    if ((mode & S_IWOTH)) zt[8] = 'w';
    if ((mode & S_IXOTH)) zt[9] = 'x';
}
void ls_l(){
    DIR *dir;
    dirent *ptr;
    struct stat file_info;
    if((dir = opendir(path)) == NULL) {
        printf("当前路径不存在\n");
        return;
    }
    while((ptr = readdir(dir)) != NULL) {
        if (ptr -> d_name[0] == '.') {
            continue;
        }
        char temp[1000];
        strcpy(temp, path);
        strcat(temp, "/");
        strcat(temp, ptr -> d_name);
        char zt[15];
        memset(zt, '-', sizeof(zt));
        zt[14] = '\0';
        stat(temp, &file_info); //得到指定文件名的描述信息
        rwx(file_info.st_mode, zt); //确定文件权限信息
        printf("%-12s ", zt);
        printf("%-7d ", file_info.st_nlink);
        printf("%-5s ", getpwuid(file_info.st_uid) -> pw_name);
        printf("%-7s ", getgrgid(file_info.st_gid) -> gr_name);
        printf("%-8d ", (int)file_info.st_size);
        printf("%-15.12s ", 4 + ctime(&file_info.st_mtime));
        printf("%-10s\n", ptr -> d_name);
         
    }
    printf("\n");
    closedir(dir);
}
void ls(char *s) {
    if (strcmp(s, "-l") == 0) {
        ls_l();
        return ;
    }
    DIR *dir;
    struct dirent *ptr;
    if ((dir = opendir(path)) == NULL) {
        printf("当前路径发生错误\n");
        exit(1);
    }
    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)
            printf("");
        else if(ptr->d_type == 8)    //file
            printf("%s ", ptr -> d_name);
         
        else if(ptr->d_type == 4)    //dir
            printf("%s ", ptr -> d_name);
    }
    printf("\n");
    closedir(dir);
    return ;
}

void inputerr()
{
    printf("输入路径格式有误\n");
    return ;
}

void cd(char *new_path) {
    char temp[1000];
    if (new_path[0] == '.') {
        strcpy(temp, path);
        if (new_path[1] == '/') {
            char temp_2[1000];
            for (int i = 1; new_path[i]; i++)
                temp_2[i - 1] = new_path[i];
            strcat(temp, temp_2);
        } else if (new_path[1] == '.') {
            int len = strlen(temp);
            for (; temp[len] != '/'; len--) continue;
            temp[len] = '\0';
        } else {
            inputerr();
            return ;
        }
    } else if (new_path[0] == '/') {
        strcpy(temp, new_path);
    } else {
        strcpy(temp, path);
        if (strlen(temp) != 1 ) strcat(temp, "/");
        strcat(temp, new_path);
    }
    
    DIR *dir;
    if ((dir = opendir(temp)) == NULL) {
        printf("%s 路径不存在\n", temp);
        return ;
    } else {
        strcpy(path, temp);
    }
    return ;
}

void process(char ord_str[10][1000]) {
        if (strcmp(ord_str[0], "ls") == 0) ls(ord_str[1]);
        else if (strcmp(ord_str[0], "cd") == 0) {
            cd(ord_str[1]);
        }else {
            char command[1000] = {0};
            for (int i = 0; i < 10; i++) {
                strcat(command, ord_str[i]);
                strcat(command, " ");
            }
            system(command);
        }
}

int main()
{
    getcwd(path, sizeof(path));
    while(1){
        hello();
        int ord_num = 0;
        char ord_str[10][1000];
        for (int i = 0; i < 10; i++) memset(ord_str[i], 0, sizeof(ord_str[i]));
        for (;~scanf("%s", ord_str[ord_num]); ord_num++){
            if(getchar() == '\n') break;
        }
        process(ord_str);
    }
    return 0;
}
