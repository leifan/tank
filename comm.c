//====================================================
//	接口驱动的.C文件
//====================================================
//说明： 
//		原版时间：	2010-05-17 
//		作    者：    trbbadboy 
//             QQ:472497084 
//         E-mail:trbbadboy@qq.com 
//		修改者：    leiyin 
//      修改时间：  2011-8-18
//====================================================  
#define  comm_GLOBALS

#include "comm.h"

//---------------------------------------------
//延时函数 
//---------------------------------------------
void delay(int i)
{
   while(i--)
   {
		waitvblank();//等待垂直中断
   }
}
//----------------------------------------------------
//读手柄函数
//----------------------------------------------------
uint8 read_joystick(uint16 _joystick)			
{
	uint8 n=8,joy_state=0;
	address(_joystick)=01;		//对_joystick写01
	address(_joystick)=00;		//对_joystick写00
	while(n){
		joy_state=(joy_state<<1)|address(_joystick)&1;
		--n;
	}
	return joy_state;
}

//----------------------------------------------------
//填充CPU的RAM
//----------------------------------------------------
void fill_RAM(uint8 *p,uint16 len,uint8 value)		
{
	while(len){
		*p=value;
		++p;
		--len;
	}
}

//----------------------------------------------------
//填充PPU的VRAM
//----------------------------------------------------
void fill_VRAM(uint16 start,uint16 len,uint8 value)	
{
	set_VRAM_add(start);
	while(len){
		address(PPU_memory_dat)=value;
		--len;
	}
}

//----------------------------------------------------
//填充精灵RAM
//----------------------------------------------------
void fill_SPRAM(uint8 start,uint8 len,uint8 value)	
{
	address(SP_memory_add)=start;
	while(len){
		address(SP_memory_dat)=value;
		--len;
	}
}

//----------------------------------------------------
//从RAM拷数据到VRAM
//----------------------------------------------------
void copy_RAM_to_VRAM(uint8 *st_r,uint16 st_v,uint16 len)	
{
	set_VRAM_add(st_v);
	while(len){
		address(PPU_memory_dat)=*st_r;
		++st_r;
		--len;
	}
}

//----------------------------------------------------
//从RAM拷数据到SPRAM
//----------------------------------------------------
void copy_RAM_to_SPRAM(uint8 *st_r,uint8 st_s,uint8 len)		
{
	address(SP_memory_add)=st_s;
	while(len){
		address(SP_memory_dat)=*st_r;
		++st_r;
		--len;
	}
}

//----------------------------------------------------
//从VRAM拷数据到RAM
//----------------------------------------------------
uint8 *copy_VRAM_to_RAM(uint16 st_v,uint8 *st_r,uint16 len)		
{
	uint8 *p=st_r;
	set_VRAM_add(st_v);
	0|address(0x2007);	//读取的第一字节被忽略，所以多读一次
	while(len){
		*st_r=address(PPU_memory_dat);
		++st_r;
		--len;
	}
	return p;
}

//----------------------------------------------------
//从SPRAM拷数据到RAM
//----------------------------------------------------
uint8 *copy_SPRAM_to_RAM(uint8 st_s,uint8 *st_r,uint8 len)		
{
	uint8 *p=st_r;
	address(SP_memory_add)=st_s;
	while(len){
		*st_r=address(SP_memory_dat);
		++st_r;
		--len;
	}
	return p;
}

//----------------------------------------------------
//精灵的DMA传输方式
//----------------------------------------------------
void SP_DMA(uint8 page,uint8 start)	
{
	address(SP_memory_add)=start;
	address(SP_DMA_access)=page;
}

//----------------------------------------------------
//读取VRAM的值
//----------------------------------------------------
uint8 read_VRAM(uint16 addr)	
{
	set_VRAM_add(addr);
	0|address(0x2007);	//读取的第一字节被忽略，所以多读一次
	return address(PPU_memory_dat);
}

//----------------------------------------------------
//写VRAM的值
//----------------------------------------------------
void write_VRAM(uint16 addr,uint8 value)	
{
	set_VRAM_add(addr);
	address(PPU_memory_dat)=value;
}

//----------------------------------------------------
//读取SPRAM的值
//----------------------------------------------------
uint8 read_SPRAM(uint8 addr)			
{

	address(SP_memory_add)=addr;
	return address(SP_memory_dat);
}

//----------------------------------------------------
//写SPRAM的值
//----------------------------------------------------
void write_SPRAM(uint8 addr,uint8 value)
{
	address(SP_memory_add)=addr;
	address(SP_memory_dat)=value;
}

//----------------------------------------------------
//向名字表_nametable的(x,y)位置写入串s 写时候关屏！
//----------------------------------------------------
void puts_xy(uint16 _nametable,uint8 _x,uint8 _y,char *s)	
{
	uint16 u;
	u=(_nametable)+(_y)*32+(_x);
	set_VRAM_add(u);
	while(*s!=NULL){
		address(PPU_memory_dat)=*s;
		s++;
	}
}

//----------------------------------------------------
//屏幕显示关
//----------------------------------------------------
void disable_graphics()		
{
	address(PPU_ctrl_reg_1) = 0;
	address(PPU_ctrl_reg_2) = 0;
}

//----------------------------------------------------
//屏幕显示开
//----------------------------------------------------
void enable_graphics()		
{//你可以自己修改这段代码来实现你的需要，具体的修改的依据你的需要，多看任天堂文件系统说明吧
	address(PPU_ctrl_reg_1) = bin(	1,0,0,1,0,0,0,0);
	address(PPU_ctrl_reg_2) = bin(	0,0,0,1,1,1,1,0);
}

//----------------------------------------------------
//声音初始化
//----------------------------------------------------
void sound_init()	
{
	address(sound_ctrl_reg) = 0x0f;
}

//----------------------------------------------------
//传入声道和四个参数
//----------------------------------------------------
void sound(uint16 ch, uint8 v0, uint8 v1, uint8 v2, uint8 v3)	
{
	address(ch++)=v0;
	address(ch++)=v1;
	address(ch++)=v2;
	address(ch++)=v3;
}

//----------------------------------------------------
//最后面是调试
//----------------------------------------------------
//用于程序的暂停，传入0不显示任何内容，非0显示调试
void nesdebug(uint8 i)	
{
	if(i){
		cprintf("Debug mode !");
		gotoxy(0,wherey()+1);
		cprintf("Press START go on....");
	}
	while(read_joy()!=button_START){}	//等待start按下
}

////---------------------------------------------
////设置背景调色板对应的调色板的颜色
////---------------------------------------------
////     n: 选择设定的调色板的标号
////     m: 选择设定的颜色号
//// color: 设定的颜色值	
//void set_color(uint8 n,uint8 m,uint8 color)
//{
//   address(0x2006)=0x3f;  
//   address(0x2006)=0x00+n*4+m;   
//   address(0x2007)=color;   
//} 
////---------------------------------------------
////设置精灵调色板对应的调色板的颜色
////--------------------------------------------- 	
//void set_SPcolor(uint8 n,uint8 m,uint8 color)
//{
//   address(0x2006)=0x3f;  
//   address(0x2006)=0x10+n*4+m;   
//   address(0x2007)=color;   
//} 	

//----------------------------------------------------
//文件结束
//----------------------------------------------------

