#include <iostream>

int main()
{
    int ans = 0;
    for (int i = 1; i <= 333; i++) {
        if (3 * i < 1000) ans += (3 * i);
        if (5 * i < 1000) ans += (5 * i);
        if (15 * i < 1000) ans -= (15 * i);
    }
    printf("%d\n", ans);
    return 0;
}
 
