//====================================================
//	接口驱动的.H文件
//====================================================
//说明： 
//		原版时间：	2010-05-17 
//		作    者：    trbbadboy 
//             QQ:472497084 
//         E-mail:trbbadboy@qq.com 
//		 修改者:   leiyin 
//      修改时间:  2011-8-18
//             QQ:675274588
//         E-mail:675274588@qq.com
//====================================================       
#ifndef _comm_h_
#define _comm_h_

#ifdef   comm_GLOBALS
#define  comm_EXT
#else
#define  comm_EXT  extern
#endif

//----------------------------------------------------
//头文件

#include "conio.h"	//包含CC65提供的库
#include "nes.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "types.h"	 //类型定义文件

//----------------------------------------------------
//宏定义

#define true	1
#define false	0
#define NULL	0

//二进制的形象表示方法，从左到右分别位第7 6 5 4 3 2 1 0位
#define bin(_a,_b,_c,_d,_e,_f,_g,_h) ((_a)<<7|(_b)<<6|(_c)<<5|(_d)<<4|(_e)<<3|(_f)<<2|(_g)<<1|(_h))	//二进制的表示

//位表示
#define bit0	0x01	//第0位
#define bit1	0x02	//第1位
#define bit2	0x04	//第2位
#define bit3	0x08	//第3位
#define bit4	0x10	//第4位
#define bit5	0x20	//第5位
#define bit6	0x40	//第6位
#define bit7	0x80	//第7位

#define upperbyte(_value)		((uint8)((_value)>>8))		//取高字节
#define lowerbyte(_value)		((uint8)(_value))			//取的字节

//------------------------------------
//手柄相关
//------------------------------------

#define joystick_1	0x4016				//两个手柄的映射
#define joystick_2	0x4017

#define button_A		0x80			//按钮A
#define button_B		0x40			//按钮B
#define button_SELECT	0x20			//按钮SELECT
#define button_START	0x10			//按钮START
#define button_UP		0x08			//按钮UP
#define button_DOWN		0x04			//按钮DOWN
#define button_UD		0x0C			//上下键掩码
#define button_LEFT		0x02			//按钮LEFT
#define button_RIGHT	0x01			//按钮RIGHT
#define button_LR		0x03			//左右键掩码
#define button_DRT		0x0F			//方向键掩码
#define button_ANY		0xff			//任意键掩码

#define presskey(k)	(key & (k))
#define iskey(k)	(key == (k))
#define downkey(k)	(((k)&okey)!=((k)&key) && (k)&key )
#define upkey(k)	(((k)&okey)!=((k)&key) && (k)&okey)
#define read_joy()  read_joystick(joystick_1)//读取手柄1的

#define presskey2(k)	(key2 & (k))
#define iskey2(k)	(key2 == (k))
#define downkey2(k)	(((k)&okey2)!=((k)&key2) && (k)&key2 )
#define upkey2(k)	(((k)&okey2)!=((k)&key2) && (k)&okey2)
#define read_joy2()  read_joystick(joystick_2)//读取手柄2的
//------------------------------------
//关于PPU控制寄存器1
//------------------------------------
#define PPU_ctrl_reg_1			0x2000	//PPU控制寄存器1映射地址

#define REG_1_name_0			0x00	//使用名字表0($2000)
#define REG_1_name_1			0x01	//使用名字表1($2400)
#define REG_1_name_2			0x02	//使用名字表2($2800)
#define REG_1_name_3			0x03	//使用名字表3($2c00)
#define REG_1_inc_32			0x04	//让PPU地址寄存器的值每次访问后增加32
#define REG_1_SP_pattern_1		0x08	//让精灵使用的图案表为图案表1($1000)
#define REG_1_IM_pattern_1		0x10	//让背景使用的图案表为图案表1($1000)
#define REG_1_SP_bigsize		0x20	//让精灵尺寸为8*16
#define REG_1_PPU_mask			0x40	//未使用
#define REG_1_VBlank_able		0x80	//在Vblank时发生中断

//------------------------------------
//关于PPU控制寄存器2
//------------------------------------

#define PPU_ctrl_reg_2			0x2001	//PPU控制寄存器2映射地址

#define REG_2_Unkown			0x01	//使用单色
#define REG_2_show_all_IM		0x02	//显示屏幕的左8列 
#define REG_2_show_all_SP		0x04	//显示精灵的左8列 
#define REG_2_IM_able			0x08	//显示图像
#define REG_2_SP_able			0x10	//显示精灵
#define REG_2_bg_color_none		0x00	//没效果
#define REG_2_bg_color_blue		0x20	//强化蓝色
#define REG_2_bg_color_green	0x40	//强化绿色
#define REG_2_bg_color_red		0x80	//强化红色


//------------------------------------
//关于PPU状态寄存器
//------------------------------------

#define PPU_status_reg			0x2002	//PPU状态寄存器映射地址

#define hit_flag				0x40	//0号精灵碰撞标志
#define VBlank_flag				0x80	//Vblank标志
#define IsVblank()				address(PPU_status_reg)&VBlank_flag//中断期间
//------------------------------------
//其他寄存器映射
//------------------------------------

#define SCR_scroll_offset		0x2005	//屏幕滚动偏移
#define PPU_memory_add			0x2006	//VRAM地址
#define PPU_memory_dat			0x2007	//VRAM数据

#define SP_memory_add			0x2003	//精灵RAM地址
#define SP_memory_dat			0x2004	//精灵RAM数据
#define SP_DMA_access			0x4014	//DMA访问精灵RAM

//------------------------------------
//VRAM内存分类
//------------------------------------
#define VRAM_pattern_0			0x0000	//图案表0
#define VRAM_pattern_1			0x1000	//图案表1
#define pattern_length			0x1000	//图案表长度
#define all_pat_len				0x2000	//全部图案表长度

#define VRAM_name_0				0x2000	//名字表（命名表）0
#define VRAM_name_1				0x2400	//名字表1
#define VRAM_name_2				0x2800	//名字表2
#define VRAM_name_3				0x2c00	//名字表3
#define name_length				0x03c0	//名字表长度



#define VRAM_attr_0				0x23c0	//属性表0
#define VRAM_attr_1				0x27c0	//属性表1
#define VRAM_attr_2				0x2bc0	//属性表2
#define VRAM_attr_3				0x2fc0	//属性表3
#define attr_length				0x0040	//属性表长度

#define full_name_l				0x0400	//单个完整的的名字表（命名表）长度
#define all_name_l				0x0800	//全部（两个）完整的的名字表（命名表）长度

#define col_black					0x0f		//黑
#define col_blue					0x02		//蓝
#define col_green					0x2a		//绿
#define col_red						0x16		//红
#define col_white					0x30		//白

#define BG_palette				0x3f00	//背景调色板
#define SP_palette				0x3f10	//精灵调色板
#define palette_len				0x0010	//单个调色板长度
#define all_pal_len				0x0020	//全部（两个）调色板长度
#define VRAM_palette			0x3f00	//调色板起始位置

//------------------------------------
//精灵相关
//------------------------------------

#define sprite_length			0x04	//单个精灵长度（4个字节）
#define sprite_all_len			0xff	//所用精灵的长度
#define	sprite_start			0x00	//精灵在SPRAM中的起始位置
#define SP_color				0x03	//颜色高两位
#define SP_behindbg				0x20	//放置于背景后
#define SP_hor					0x40	//水平翻转
#define SP_ver					0x80	//垂直翻转

//------------------------------------
//其他
//------------------------------------

#define screen_width			32		//画面宽
#define screen_height			30		//画面高


#define wait_VBlank()			while(!((address(PPU_status_reg) & VBlank_flag)))	//等待VBlank
#define ishit()					(address(PPU_status_reg) & hit_flag)		//判断0号精灵是否发生碰撞

#define set_VRAM_add(_add)		address(PPU_memory_add)=upperbyte(_add),\
									address(PPU_memory_add)=lowerbyte(_add)		//设置VRAM地址
#define set_cREG_1(_v)			address(PPU_ctrl_reg_1)=(_v)	//设置控制寄存器1
#define set_cREG_2(_v)			address(PPU_ctrl_reg_2)=(_v)	//设置控制寄存器2

#define putc_xy(_nametable,_x,_y,_c)	write_VRAM((_nametable)+(_y)*32+(_x),_c)	//向_nametable的(x,y)位置写入c
#define getc_xy(_nametable,_x,_y)			read_VRAM((_nametable)+(_y)*32+(_x))	//读_nametable的(x,y)位置的值

#define set_scroll(_h,_v)	address(SCR_scroll_offset)=_h,\
													address(SCR_scroll_offset)=_v		//设置屏幕滚动
													

//------------------------------------
//图案表相关
//------------------------------------

#define load_pattern_0(_ptr)		copy_RAM_to_VRAM(_ptr,VRAM_pattern_0,pattern_length)	//载入图案表0
#define load_pattern_1(_ptr)		copy_RAM_to_VRAM(_ptr,VRAM_pattern_1,pattern_length)	//载入图案表0											
#define load_all_pattern(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_pattern_1,all_pat_len)		//载入全部（两个）图案表
													

//------------------------------------
//调色板相关
//------------------------------------
#define load_SP_palette(_ptr)		copy_RAM_to_VRAM(_ptr,SP_palette,palette_len)	//载入精灵调色板
#define load_BG_palette(_ptr) 	copy_RAM_to_VRAM(_ptr,BG_palette,palette_len)	//载入背景调色板
#define load_all_palette(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_palette,all_pal_len)	//载入全部(两个)调色板
#define load_palette_n(_ptr,_n)	copy_RAM_to_VRAM(_ptr,VRAM_palette+(_n)*4,4)	//载入第n个色盘(背景开始数，第一个背景调色板为0,第一个精灵调色板为4)
								
#define save_SP_palette(_ptr)		copy_VRAM_to_RAM(SP_palette,_ptr,palette_len)	//保存精灵调色板
#define save_BG_palette(_ptr)		copy_VRAM_to_RAM(BG_palette,_ptr,palette_len)	//保存背景调色板
#define save_all_palette(_ptr)	copy_VRAM_to_RAM(VRAM_palette,_ptr,all_pal_len)	//保存全部(两个)调色板
								
								
											//about name table
#define load_name_table_0(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_name_0,name_length)	//载入名字表0
#define load_name_table_1(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_name_1,name_length)	//载入名字表1
#define load_full_name_0(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_name_0,full_name_l)	//载入完整的名字表0(包括属性表0)
#define load_full_name_1(_ptr)	copy_RAM_to_VRAM(_ptr,VRAM_name_1,full_name_l)	//载入完整的名字表1(包括属性表1)
#define load_all_name(_ptr)			copy_RAM_to_VRAM(_ptr,VRAM_name_0,all_name_l)	//载入全部的名字表(两个名字表和两个属性表)

#define cls_name_table_0()			fill_VRAM(VRAM_name_0,name_length,0)
#define cls_name_table_1()			fill_VRAM(VRAM_name_1,name_length,0)
#define cls_all_name()					fill_VRAM(VRAM_name_0,all_name_l,0)
#define fill_name_0(_v)					fill_VRAM(VRAM_name_0,name_length,_v)
#define fill_name_1(_v)					fill_VRAM(VRAM_name_1,name_length,_v)


//------------------------------------
//直接传入精灵
//------------------------------------

#define putSP(n,x,y,t,a) 	address(SP_memory_add)=((n)<<2),\
							address(SP_memory_dat)=y,\
							address(SP_memory_dat)=t,\
							address(SP_memory_dat)=a,\
							address(SP_memory_dat)=x
#define ShowSP()            address(PPU_ctrl_reg_2)=bin(0,0,0,1,1,1,1,0)  //显示精灵
#define HideSP()            address(PPU_ctrl_reg_2)=bin(0,0,0,0,1,1,1,0)  //隐藏精灵
typedef struct		//定义精灵结构
{
	uint8 y;			//y坐标
	uint8 tile;		//Tile索引号
	uint8 attr;		//属性:vhp000cc(垂直翻转 水平翻转 背景优先权 000 颜色的高2位)
	uint8 x;			//x坐标
	uint8 dir;        //方向
}SPRITE,*pSPRITE;


//------------------------------------
//关于声音(目前只支持前两个声道)
//------------------------------------

#define sound_chn_0    0x4000 //声道0（方波1）
#define sound_chn_1    0x4004 //声道1（方波2）
#define sound_chn_2    0x4008 //声道2
#define sound_chn_3    0x400c //声道3
#define sound_ctrl_reg 0x4015	//声道使能控制

//------------------------------------
//v1.1修正
//------------------------------------

#define rnd(n)	(n*(rand()&0x00ff))/0x0100	//产生不大于n的随机数


//====================================================================
//                 函数声明										 //
//====================================================================
//----------------------------------------------------
//延时函数
//----------------------------------------------------
void delay(int i);
//----------------------------------------------------
//读手柄函数
//----------------------------------------------------
uint8 read_joystick(uint16 _joystick);		

//----------------------------------------------------
//填充CPU的RAM
//----------------------------------------------------
void fill_RAM(uint8 *p,uint16 len,uint8 value);		

//----------------------------------------------------
//填充PPU的VRAM
//----------------------------------------------------
void fill_VRAM(uint16 start,uint16 len,uint8 value);	

//----------------------------------------------------
//填充精灵RAM
//----------------------------------------------------
void fill_SPRAM(uint8 start,uint8 len,uint8 value);	

//----------------------------------------------------
//从RAM拷数据到VRAM
//----------------------------------------------------
void copy_RAM_to_VRAM(uint8 *st_r,uint16 st_v,uint16 len);	

//----------------------------------------------------
//从RAM拷数据到SPRAM
//----------------------------------------------------
void copy_RAM_to_SPRAM(uint8 *st_r,uint8 st_s,uint8 len);		

//----------------------------------------------------
//从VRAM拷数据到RAM
//----------------------------------------------------
uint8 *copy_VRAM_to_RAM(uint16 st_v,uint8 *st_r,uint16 len);		

//----------------------------------------------------
//从SPRAM拷数据到RAM
//----------------------------------------------------
uint8 *copy_SPRAM_to_RAM(uint8 st_s,uint8 *st_r,uint8 len);		

//----------------------------------------------------
//精灵的DMA传输方式
//----------------------------------------------------
void SP_DMA(uint8 page,uint8 start);

//----------------------------------------------------
//读取VRAM的值
//----------------------------------------------------
uint8 read_VRAM(uint16 addr);	

//----------------------------------------------------
//写VRAM的值
//----------------------------------------------------
void write_VRAM(uint16 addr,uint8 value);	

//----------------------------------------------------
//读取SPRAM的值
//----------------------------------------------------
uint8 read_SPRAM(uint8 addr);			

//----------------------------------------------------
//写SPRAM的值
//----------------------------------------------------
void write_SPRAM(uint8 addr,uint8 value);

//----------------------------------------------------
//向名字表_nametable的(x,y)位置写入串s 写时候关屏！
//----------------------------------------------------
void puts_xy(uint16 _nametable,uint8 _x,uint8 _y,char *s);	

//----------------------------------------------------
//屏幕显示关
//----------------------------------------------------
void disable_graphics();		

//----------------------------------------------------
//屏幕显示开
//----------------------------------------------------
void enable_graphics();		

//----------------------------------------------------
//声音初始化
//----------------------------------------------------
void sound_init();	

//----------------------------------------------------
//传入声道和四个参数
//----------------------------------------------------
void sound(uint16 ch, uint8 v0, uint8 v1, uint8 v2, uint8 v3);	

//----------------------------------------------------
//最后面是调试
//----------------------------------------------------
//用于程序的暂停，传入0不显示任何内容，非0显示调试
void nesdebug(uint8 i);	

#endif //文件结束