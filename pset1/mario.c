#include <cs50.h>
#include <stdio.h>

int main(void) {
    int height = 0;
    int sharps = 0;
    int spaces = 0;
    
    do {
        printf("Height: ");
        height = get_int();
    } while (height < 0 || height > 23);
    
    for (int i=0; i<height; i++) {

        spaces = height - i - 1; 
        sharps = height - spaces;
        
        for (int x=0; x < spaces; x++) {
            printf(" ");
        }
        for (int x=0; x < sharps; x++) {
            printf("#");
        }
        
        printf("  ");
        
        for (int x=0; x < sharps; x++) {
            printf("#");
        }
        
        printf("\n");
        
    }
    return 0;
}