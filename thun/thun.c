#include <todo.h>
#include <stdio.h>
#include <string.h>
#include <bmp.h>

// 2019/3/18/17点47分 此处莫名报错，得在void前加一个分号才可以 ，报错信息
// 已解决，头文件的问题。
/*
make.exe[2]: Entering directory `C:/Users/13252/Desktop/AntzS/AntzOS'
cc1.exe -I include/ -Os -Wall -quiet -o thun/thun.gas thun/thun.c
thun/thun.c:6: parse error before "void"
make.exe[2]: *** [thun/thun.gas] Error 1
*/

void to_printf_dijkstra(){
    to_show() ;
}

void to_show(){
  struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
  int  x, y ,printx,printy;
  int k ; // 1024x768
    k = 0  ;
    for (y = 0; y < 16; y++) { //10800  108 * 13
      for (x = 0; x < 21; x++){
       // 16 + bmp_r[k]/43 + 6* (bmp_g[k]/43) + 36* (bmp_b[k]/43) ;
       for (printy=0; printy<50;printy++){
        for (printx=0; printx<50; printx++){
            print_area(binfo->vram, binfo->scrnx,diban[printx][printy],x*50+printx,y*50+printy,x*50+printx,y*50+printy);
        }
       }
      }
    }
}


void to_printf_pdd(){
   struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
   int x, y;
   int k = 0 ;
   for (y = 0; y < 100; y++) {
     for (x = 0; x < 100; x++){ //100
        if(linus[k]!=231){
            print_area(binfo->vram, binfo->scrnx , linus[k] , x+binfo->scrnx-500, y+215, x+binfo->scrnx-500, y+215);
        }
       k++;
     }
   }
}

void to_printf_slm(int base_x, int base_y){
   struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
   int x, y;
   int k = 0 ;
   for (y = 0; y < 27; y++) {
     for (x = 0; x < 40; x++){ //100
        if(slm[k]!=231){
            print_area(binfo->vram, binfo->scrnx , slm[k] ,
            base_x+x*2, base_y + y*2, base_x + x*2+2, base_y+y*2+2);
        }
       k++;
     }
   }
}

void to_printf_linus(int base_x, int base_y){
   struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
    print_string(binfo->vram, binfo->scrnx,  base_x-20,  base_y-30, COL8_FFFFFF, "LV.99 Linus");
   int x, y;
   int k = 0 ;
   for (y = 0; y < 67; y++) {
     for (x = 0; x < 52; x++){ //100
        if(linus[k]!=231){
            print_area(binfo->vram, binfo->scrnx , linus[k] , base_x+x, base_y+y, base_x+x, base_y+y);
        }
       k++;
     }
   }
}
