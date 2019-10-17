/* 定时器 */

#include <todo.h>

#define PIT_CTRL	0x0043
#define PIT_CNT0	0x0040

struct TIMERCTL timerctl;

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
int old_time = 0;

void init_data(void){
	i= 0;
	j= 0;
}

void inthandler20(int *esp)
{
	io_out8(PIC0_OCW2, 0x60); /* 把IRQ-00信号接收完了的信息通知给PIC */
	timerctl.count++;
	old_time ++ ;
	struct BOOTINFO *binfo = (struct BOOTINFO *) ADR_BOOTINFO;
	// 绘制
	if((timerctl.flag==1)&&(old_time%10==0)){
		
		print_area(binfo->vram, binfo->scrnx,COL8_FFFFFF,pyx,pyy,pyx+10,pyy+10);
		
		// exit 
		if(j>=205){
			timerctl.flag = 0 ;
			init_screen8(binfo->vram, binfo->scrnx, binfo->scrny);
			print_string(binfo->vram, binfo->scrnx,  0,  0, COL8_FFFFFF, "Terminal-Antz");
			print_string(binfo->vram, binfo->scrnx,  0,  0, COL8_000000, "Terminal-Antz");
			print_string(binfo->vram, binfo->scrnx,  binfo->scrnx/2-60,  0, COL8_000000, "|-|o|x|");
			print_string(binfo->vram, binfo->scrnx, 4, 19, COL8_FFFFFF, "AntzOS> SayHello()");
			print_string(binfo->vram, binfo->scrnx, 4, 38, COL8_FFFFFF, "Hello My AntzOs.");
			print_string(binfo->vram, binfo->scrnx, 4, 57, COL8_FFFFFF, "AntzOS>");
		}
	}
	return;
}
/*
int print_x = binfo->scrnx -70 ;
int print_y = binfo->scrny -40 ;

print_area(binfo->vram, binfo->scrnx,COL8_FFFFFF,print_x,print_y,print_x+60,print_y+35);

print_area(binfo->vram, binfo->scrnx,COL8_FFFFFF,print_x+10,print_y-20,print_x+20,print_y);
		print_area(binfo->vram, binfo->scrnx,COL8_008400,print_x+12,print_y-17,print_x+18,print_y);

print_area(binfo->vram, binfo->scrnx,COL8_FFFFFF,print_x+40,print_y-20,print_x+50,print_y);
		print_area(binfo->vram, binfo->scrnx,COL8_008400,print_x+42,print_y-17,print_x+48,print_y);


print_area(binfo->vram, binfo->scrnx,timerctl.count%15,print_x+13,print_y+13,print_x+18,print_y+22);
print_area(binfo->vram, binfo->scrnx,timerctl.count%15,print_x+43,print_y+13,print_x+48,print_y+22);

print_area(binfo->vram, binfo->scrnx,COL8_840000,print_x+22,print_y+25,print_x+40,print_y+30);

print_area(binfo->vram, binfo->scrnx,timerctl.count%15  ,print_x+27,print_y+25,print_x+30,print_y+27);
print_area(binfo->vram, binfo->scrnx,timerctl.count%14+1,print_x+30,print_y+25,print_x+33,print_y+27);
*/
