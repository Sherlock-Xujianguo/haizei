#include <stdio.h>
#include "scan_keyboard.h"
int i = 0;
int main()
{
    while (1) {
        printf("%d\n", scanKeyboard());
        printf("%d\n", scanKeyboard());    
    }
    return 0;
}
