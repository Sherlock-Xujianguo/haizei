/*================================================================
*   
*   
*   文件名称：1131.cpp
*   创 建 者：Sherlock_XuJianguo
*   创建日期：2019年01月09日
*   描    述：
*
================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <malloc.h>
#define max_n 500000

using namespace std;

struct Node{
    int num;
    int t;
    int deep;
    Node *next;
};

struct Node map[max_n];

void init(int n) {
    for (int i = 1; i <= n; i++) {
        map[i].num = i;
        map[i].t = map[i].deep = 0;
        map[i].next = NULL;
    }
    return ;
}

void add(int a, int b, int t) {
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    struct Node *p = &(map[a]);
    while(p -> next != NULL) {
        p = p -> next;
    }
    p -> next = temp;
    temp -> num = b;
    temp -> t = t;
    temp -> next = NULL;
    return ;
}

void depth(int root) {
    stack <int> s;
    s.push(root);
    while (s.size()) {
        int temp = s.top();
        s.pop();
        struct Node *p = map[temp].next;
        while (p != NULL) {
            if (p -> num == root || map[p -> num].deep != 0) {
                p = p -> next;
                continue;
            }
            map[p -> num].deep = map[temp].deep + 1;
            s.push(p -> num);
            p = p -> next;
        }
    }
    return ;
}

int rst = 0;

int dfs(int father) {
    if (map[father].next == NULL) return 0;
    if (map[father].next -> next == NULL) return 0;
    
    int max_t = 0;
    int son_num = 0;
    int temp;
    struct Node *p = map[father].next;
    while (p != NULL) {
        if (map[p -> num].deep < map[father].deep) {
            p = p -> next;
            continue;
        } 

        int temp = dfs(p -> num) + (p -> t);
        
        if (temp == max_t) {
            son_num++;
            p = p -> next;
            continue;
        }
        if (temp > max_t) {
            rst += ((temp - max_t) * son_num);
            max_t = temp;
            son_num++;
        } else {
            rst += (max_t - temp);
            son_num++;
        }
        p = p -> next;
    }
    return max_t;
}


int main()
{
    int n;
    scanf("%d", &n);
    init(n);

    int root;
    scanf("%d", &root);

    for (int i = 0; i < n - 1; i++) {
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        add(a, b, t);
        add(b, a, t);
    }
    
    depth(root);
    dfs(root);
    printf("%d\n", rst);
    
    

    return 0;
}
