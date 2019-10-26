/* 定时器 */

#include <todo.h>

#define PIT_CTRL	0x0043
#define PIT_CNT0	0x0040

struct TIMERCTL timerctl;

int local_pyx = 0;
int local_pyy = 0;

void init_pit(void)
{
	io_out8(PIT_CTRL, 0x34);
	io_out8(PIT_CNT0, 0x9c);
	io_out8(PIT_CNT0, 0x2e);
	
	timerctl.count = 0;
	timerctl.flag = 0 ;
	return;
}


int i,j = 0 ;
void init_data(void){
	i= 0;
	j= 0;
}


void inthandler20(int *esp)
{
	io_out8(PIC0_OCW2, 0x60); /* 把IRQ-00信号接收完了的信息通知给PIC */
	timerctl.count++;
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;

	// 绘制
	if((timerctl.flag==1)){

        if((local_pyx!=pyx) || (local_pyy!=pyy)){
            local_pyx = pyx ;
            local_pyy = pyy ;
            to_show();
            header();
//            to_printf_self(pyx,pyy);
//            to_printf_slm();
        }
        show_linus(binfo->scrnx-100,binfo->scrny-200);
//		print_area(binfo->vram, binfo->scrnx,55, 0, 0, binfo->scrnx, binfo->scrny);

	}
	return;
}


void header(){
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;

    print_area(binfo->vram, binfo->scrnx,51, pyx-20, pyy-30, pyx+20, pyy-15);
    // face
	print_area(binfo->vram, binfo->scrnx,COL8_00FF00, pyx-17, pyy-20, pyx+17, pyy+15);
    // eye
    print_area(binfo->vram, binfo->scrnx,12, pyx-10, pyy-20, pyx-2, pyy-12);
    print_area(binfo->vram, binfo->scrnx,12, pyx+2, pyy-20, pyx+10, pyy-12);

    print_area(binfo->vram, binfo->scrnx,12, pyx-10, pyy-5, pyx+10, pyy);

    // hand
    print_area(binfo->vram, binfo->scrnx,12, pyx-35, pyy+20, pyx-20, pyy+30);

    // 剑
    print_area(binfo->vram, binfo->scrnx,53, pyx-30, pyy-25, pyx-25, pyy+40);

    // body
    print_area(binfo->vram, binfo->scrnx,150, pyx-20, pyy+15, pyx+20, pyy+40);

    print_area(binfo->vram, binfo->scrnx,150, pyx-20, pyy+40, pyx-12, pyy+55);
    print_area(binfo->vram, binfo->scrnx,150, pyx+12, pyy+40, pyx+20, pyy+55);
    // stand 盾牌
    print_area(binfo->vram, binfo->scrnx,71, pyx+20, pyy-10, pyx+50, pyy+50);
    print_area(binfo->vram, binfo->scrnx,73, pyx+25, pyy-5, pyx+45, pyy+45);
}

void show_linus(int x, int y){
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	print_area(binfo->vram, binfo->scrnx,150, x-20, y+15, x+20, y+40);

    print_area(binfo->vram, binfo->scrnx,150, x-20, y+40, x-12, y+55);
    print_area(binfo->vram, binfo->scrnx,150, x+12, y+40, x+20, y+55);
    // hand
    print_area(binfo->vram, binfo->scrnx,12, pyx-35, pyy+20, pyx-20, pyy+30);
    to_printf_linus(x-25,y-45);

}