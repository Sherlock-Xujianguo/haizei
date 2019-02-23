#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

using namespace std;

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node {
    char c;
    int flag;
    struct Node *left, *right;
};

struct Node *root = (struct Node *)malloc(sizeof(struct Node));

void add(string temp) {
    int length = temp.length();
    struct Node *p = root;

    for (int i = 0; i < length; i++) {
        if (p -> left == NULL) {
            struct Node *sp = (struct Node *)malloc(sizeof(struct Node));
            sp -> c = temp[i];
            sp -> flag = 0;
            sp -> left = sp -> right = NULL;
            p -> left = sp;
            p = p -> left;
            if (i == length - 1) {
                sp -> flag = 1;
            }
        } else if (p -> left -> c == temp[i]) {
            p = p -> left;
        } else {
            p = p -> left;
            while (p -> right != NULL && p -> c != temp[i]) {
                p = p -> right;
            }
            if (p -> c == temp[i]) continue;
            struct Node *sp = (struct Node *)malloc(sizeof(struct Node));
            sp -> c = temp[i];
            sp -> flag = 0;
            sp -> left = sp -> right = NULL;
            p -> right = sp;
            p = p -> right;
            if (i == length - 1) {
                sp -> flag = 1;
            }
        }
    }
}

int cal(struct Node *p) {
    int left = 0;
    int right = 0;
    if (p -> left != NULL) left = cal(p -> left);
    if (p -> right != NULL) right = cal(p -> right);
    return max(p -> flag + left, right);
}


int main()
{
    root -> flag = 0;
    root -> left = root ->right = NULL;
    int n;
    scanf("%d", &n);
    getchar();
    string temp;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        add(temp);
    }

    printf("%d\n", cal(root));
    return 0;
}
