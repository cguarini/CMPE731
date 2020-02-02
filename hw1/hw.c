#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define MASK_64 (0xFFFFFFFF)
#define MASK_65 (0x1FFFFFFFF)
#define MASK_66 (0x3FFFFFFFF)
#define MASK_4 (0xF)

int main(int argc, char * argv) {
    //Suprised this type even exists
    __int128_t input = 0;
    __int128_t counter = 0;
    __int128_t mask1 = 0b101;
    __int128_t mask2 = 0b010;
    __int128_t isolationMask = 0b111;

    //Try and find
    while(input < MASK_65){
        for(int i = 0; i < 63; i++){
            if(((input & (isolationMask << i)) == (mask1 << i)) || ((input & (isolationMask << i)) == (mask2 << i))){
                //printf("%x\n\r", (int) input);
                counter++;
                break;
            }
        }
        input++;
    }
    printf("Counter found %d matches!", (int) counter);
}
 