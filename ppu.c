#include "ppu.h"
#include <raylib.h>


void draw_tile(u8 fbyte, u8 sbyte, u32 * j){
    u8 pixel_size = 2;
    u8 offset = 0;
    // if(*j > 32 * pixel_size){ 
    //     offset = 9; 
    //     *j = 9 * pixel_size;
    // }
    for(i8 i = 7; i >= 0; i--){
        u8 pixel_color = ((fbyte >> i) & 1) | (((sbyte >> i) & 1) << 1);
        printf("%d %d %d\n", pixel_color, i, fbyte);
        switch (pixel_color) {
            case 3:
                DrawRectangle(*j, offset * pixel_size , pixel_size, pixel_size, BLACK);
                break;
            case 2:
                DrawRectangle( *j, offset * pixel_size , pixel_size, pixel_size, DARKGRAY);
                break;
            case 1:
                DrawRectangle(*j, offset * pixel_size , pixel_size, pixel_size, LIGHTGRAY);
                break;
            case 0:
                DrawRectangle(*j, offset * pixel_size , pixel_size, pixel_size, WHITE);
                break;
            default:
                printf("eror parsing color");
        }
        
        offset++;
    }
    *j += pixel_size;


}