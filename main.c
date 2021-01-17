#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include <stdlib.h>
#include <intrinsic.h>
#include "int.h"

struct sp1_Rect full_screen = {0, 0, 32, 24};

extern unsigned char bubble_col1[];
extern unsigned char bubble_col2[];

struct my_sprite {
    struct sp1_ss *s;
    uint8_t x, y;
};
struct my_sprite bubble1;
struct my_sprite bubble2;

struct sp1_cs brick_object;
struct sp1_cs brick_object2;
struct sp1_cs window_object;
struct sp1_update *bricks_update;

// get the player keys input and update our sprite x/y
void get_movement(){

    if (in_key_pressed( IN_KEY_SCANCODE_q )) {
        --bubble1.y;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_a )) {
        ++bubble1.y;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_o )) {
        --bubble1.x;
    }
    if (in_key_pressed( IN_KEY_SCANCODE_p )) {
        ++bubble1.x;
    }

}

// create sprite bubbles
void create_bubbles() {

    bubble1.s = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)bubble_col1, 10);
    sp1_AddColSpr(bubble1.s, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)bubble_col2, 10);
    sp1_AddColSpr(bubble1.s, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 10);
    bubble1.x = 110;
    bubble1.y = 90;

    bubble2.s = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, 3, (int)bubble_col1, 10);
    sp1_AddColSpr(bubble2.s, SP1_DRAW_MASK2,    SP1_TYPE_2BYTE, (int)bubble_col2, 10);
    sp1_AddColSpr(bubble2.s, SP1_DRAW_MASK2RB,  SP1_TYPE_2BYTE, 0, 10);
    bubble2.x = 115;
    bubble2.y = 100;    
}

// Change the plan property taking Y value into account
void change_plan(unsigned int count, struct sp1_cs *c)
{
    (void)count;

    if(bubble1.y < bubble2.y) {
        c->plane = 15;              // Move sprite behind
    } else
    {
        c->plane = 5;               // Move sprite to front
    }
    
}

// Invalidate the sprite region, forcing SP1 to redraw it
// void invalidate_sprite(unsigned int count, struct sp1_update *u)
// {
//     (void)count;
//     sp1_InvUpdateStruct(u);
// }

int main() {

    zx_border(INK_WHITE);

    setup_int();

    sp1_Initialize(SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                   INK_WHITE | PAPER_BLACK, 'X' );
            
    sp1_Invalidate(&full_screen);

    create_bubbles();

    while(1) {

        get_movement();

        sp1_MoveSprPix(bubble1.s, &full_screen, 0, ++bubble1.x, bubble1.y);
        sp1_MoveSprPix(bubble2.s, &full_screen, 0, ++bubble2.x, bubble2.y);

        sp1_IterateSprChar(bubble1.s, change_plan);

        // Invalidates the sprite, forcing SP1 to redraw it
        // Check if it's needed or not
        //sp1_IterateUpdateSpr(bubble1.s, invalidate_sprite);

        intrinsic_halt();
        sp1_UpdateNow();
    }
}