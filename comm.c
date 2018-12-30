//====================================================
//	�ӿ�������.C�ļ�
//====================================================
//˵���� 
//		ԭ��ʱ�䣺	2010-05-17 
//		��    �ߣ�    trbbadboy 
//             QQ:472497084 
//         E-mail:trbbadboy@qq.com 
//		�޸��ߣ�    leiyin 
//      �޸�ʱ�䣺  2011-8-18
//====================================================  
#define  comm_GLOBALS

#include "comm.h"

//---------------------------------------------
//��ʱ���� 
//---------------------------------------------
void delay(int i)
{
   while(i--)
   {
		waitvblank();//�ȴ���ֱ�ж�
   }
}
//----------------------------------------------------
//���ֱ�����
//----------------------------------------------------
uint8 read_joystick(uint16 _joystick)			
{
	uint8 n=8,joy_state=0;
	address(_joystick)=01;		//��_joystickд01
	address(_joystick)=00;		//��_joystickд00
	while(n){
		joy_state=(joy_state<<1)|address(_joystick)&1;
		--n;
	}
	return joy_state;
}

//----------------------------------------------------
//���CPU��RAM
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
//���PPU��VRAM
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
//��侫��RAM
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
//��RAM�����ݵ�VRAM
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
//��RAM�����ݵ�SPRAM
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
//��VRAM�����ݵ�RAM
//----------------------------------------------------
uint8 *copy_VRAM_to_RAM(uint16 st_v,uint8 *st_r,uint16 len)		
{
	uint8 *p=st_r;
	set_VRAM_add(st_v);
	0|address(0x2007);	//��ȡ�ĵ�һ�ֽڱ����ԣ����Զ��һ��
	while(len){
		*st_r=address(PPU_memory_dat);
		++st_r;
		--len;
	}
	return p;
}

//----------------------------------------------------
//��SPRAM�����ݵ�RAM
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
//�����DMA���䷽ʽ
//----------------------------------------------------
void SP_DMA(uint8 page,uint8 start)	
{
	address(SP_memory_add)=start;
	address(SP_DMA_access)=page;
}

//----------------------------------------------------
//��ȡVRAM��ֵ
//----------------------------------------------------
uint8 read_VRAM(uint16 addr)	
{
	set_VRAM_add(addr);
	0|address(0x2007);	//��ȡ�ĵ�һ�ֽڱ����ԣ����Զ��һ��
	return address(PPU_memory_dat);
}

//----------------------------------------------------
//дVRAM��ֵ
//----------------------------------------------------
void write_VRAM(uint16 addr,uint8 value)	
{
	set_VRAM_add(addr);
	address(PPU_memory_dat)=value;
}

//----------------------------------------------------
//��ȡSPRAM��ֵ
//----------------------------------------------------
uint8 read_SPRAM(uint8 addr)			
{

	address(SP_memory_add)=addr;
	return address(SP_memory_dat);
}

//----------------------------------------------------
//дSPRAM��ֵ
//----------------------------------------------------
void write_SPRAM(uint8 addr,uint8 value)
{
	address(SP_memory_add)=addr;
	address(SP_memory_dat)=value;
}

//----------------------------------------------------
//�����ֱ�_nametable��(x,y)λ��д�봮s дʱ�������
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
//��Ļ��ʾ��
//----------------------------------------------------
void disable_graphics()		
{
	address(PPU_ctrl_reg_1) = 0;
	address(PPU_ctrl_reg_2) = 0;
}

//----------------------------------------------------
//��Ļ��ʾ��
//----------------------------------------------------
void enable_graphics()		
{//������Լ��޸���δ�����ʵ�������Ҫ��������޸ĵ����������Ҫ���࿴�������ļ�ϵͳ˵����
	address(PPU_ctrl_reg_1) = bin(	1,0,0,1,0,0,0,0);
	address(PPU_ctrl_reg_2) = bin(	0,0,0,1,1,1,1,0);
}

//----------------------------------------------------
//������ʼ��
//----------------------------------------------------
void sound_init()	
{
	address(sound_ctrl_reg) = 0x0f;
}

//----------------------------------------------------
//�����������ĸ�����
//----------------------------------------------------
void sound(uint16 ch, uint8 v0, uint8 v1, uint8 v2, uint8 v3)	
{
	address(ch++)=v0;
	address(ch++)=v1;
	address(ch++)=v2;
	address(ch++)=v3;
}

//----------------------------------------------------
//������ǵ���
//----------------------------------------------------
//���ڳ������ͣ������0����ʾ�κ����ݣ���0��ʾ����
void nesdebug(uint8 i)	
{
	if(i){
		cprintf("Debug mode !");
		gotoxy(0,wherey()+1);
		cprintf("Press START go on....");
	}
	while(read_joy()!=button_START){}	//�ȴ�start����
}

////---------------------------------------------
////���ñ�����ɫ���Ӧ�ĵ�ɫ�����ɫ
////---------------------------------------------
////     n: ѡ���趨�ĵ�ɫ��ı��
////     m: ѡ���趨����ɫ��
//// color: �趨����ɫֵ	
//void set_color(uint8 n,uint8 m,uint8 color)
//{
//   address(0x2006)=0x3f;  
//   address(0x2006)=0x00+n*4+m;   
//   address(0x2007)=color;   
//} 
////---------------------------------------------
////���þ����ɫ���Ӧ�ĵ�ɫ�����ɫ
////--------------------------------------------- 	
//void set_SPcolor(uint8 n,uint8 m,uint8 color)
//{
//   address(0x2006)=0x3f;  
//   address(0x2006)=0x10+n*4+m;   
//   address(0x2007)=color;   
//} 	

//----------------------------------------------------
//�ļ�����
//----------------------------------------------------

