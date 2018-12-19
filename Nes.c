//tank 2011
#include "comm.h"           	//�ӿ�������.H�ļ�
#include "tank_strat_map.h" 	//��ʼ�����ͼ����
#include "tank_strat_col.h" 	//��ʼ�����ɫ����Ϣ
#include "tank_sp_col.h"    	//�����ɫ����Ϣ
#include "tank_stage_map.h" 	//�ؿ��׶λ����ͼ����
#include "tank_stage_col.h" 	//�ؿ��׶λ����ɫ����Ϣ
#include "tank_task_map.h" 		//task�����ͼ����
#include "tank_task_map_back.h" //task�����ͼ���ݱ���
#include "tank_task_col.h" 		//task�����ɫ����Ϣ
#include "tank_about_map.h" 	//about�����ͼ����
#include "tank_about_col.h" 	//about�����ɫ����Ϣ

//---------------------------------------------
//�궨��

//PPU��ַ�Ĵ�����λ
#define EW()	address(PPU_memory_add)=0;\
							address(PPU_memory_add)=0
//���������λ
#define ES()			address(SCR_scroll_offset)=0;\
							address(SCR_scroll_offset)=0
//��ѧ��ʽ
#define abs_s(_a,_b)  (_a)>(_b)? ((_a)-(_b)):((_b)-(_a))	//���Բ�
						
//��ʼ�����й�
#define     START_X         80	//start (80,138)	
#define     START_Y         138
#define     ABOUT_X         80	// about (80,160)
#define     ABOUT_Y         160
//Pro_State
#define     PRO_START		 1   //��ʼ����״̬
#define     PRO_GAME		 2   //��Ϸ����״̬
#define     PRO_ABOUT		 3   //about����״̬
#define     PRO_GAMEOVER	 5   //��Ϸ����״̬
#define     IsStart()	  ( pro_state==PRO_START )  //��ʼ״̬
#define     IsGame()	  ( pro_state==PRO_GAME  )  //��Ϸ״̬
#define     IsAbout()	  ( pro_state==PRO_ABOUT )  //ABOUT״̬
#define     IsGameOver()  ( pro_state==PRO_GAMEOVER  )  //��Ϸ����״̬
//̹�˾���	��Ӧ��tile������
#define     AUTOTIME            0x80 //0x80
#define     BULLET_SPEED          4
#define     YELLOW_TANK			0x00
#define     GREEN_TANK			0x01
#define     WHITE_TANK			0x02
#define     RED_TANK			0x03

#define     SP_TANK_NUM		    8

#define     DIR_UP			    0x01
#define     DIR_DOWN			0x02
#define     DIR_RIGHT			0x04
#define     DIR_LEFT			0x08
#define     DIR_CHANGE			0x80
#define     DIR_CLR_CHANGE		0x7F


#define     RIGHT_2(_TANK)	   ((_TANK)<<2)

#define     TANK0_UP_0          0   
#define     TANK0_UP_1          RIGHT_2(1)
#define     TANK0_RIGHT_0       RIGHT_2(2)   
#define     TANK0_RIGHT_1       RIGHT_2(3)
#define     TANK0_DOWN_0        RIGHT_2(4)   
#define     TANK0_DOWN_1        RIGHT_2(5) 
#define     TANK0_LEFT_0        RIGHT_2(6)   
#define     TANK0_LEFT_1        RIGHT_2(7) 

#define     TANK1_UP_0          RIGHT_2(8)   
#define     TANK1_UP_1          RIGHT_2(9)
#define     TANK1_RIGHT_0       RIGHT_2(10)   
#define     TANK1_RIGHT_1       RIGHT_2(11)
#define     TANK1_DOWN_0        RIGHT_2(12)   
#define     TANK1_DOWN_1        RIGHT_2(13) 
#define     TANK1_LEFT_0        RIGHT_2(14)   
#define     TANK1_LEFT_1        RIGHT_2(15) 

#define     TANK2_UP_0          RIGHT_2(16)   
#define     TANK2_UP_1          RIGHT_2(17)
#define     TANK2_RIGHT_0       RIGHT_2(18)   
#define     TANK2_RIGHT_1       RIGHT_2(19)
#define     TANK2_DOWN_0        RIGHT_2(20)   
#define     TANK2_DOWN_1        RIGHT_2(21) 
#define     TANK2_LEFT_0        RIGHT_2(22)   
#define     TANK2_LEFT_1        RIGHT_2(23) 

#define     TANK3_UP_0          RIGHT_2(24)   
#define     TANK3_UP_1          RIGHT_2(25)
#define     TANK3_RIGHT_0       RIGHT_2(26)   
#define     TANK3_RIGHT_1       RIGHT_2(27)
#define     TANK3_DOWN_0        RIGHT_2(28)   
#define     TANK3_DOWN_1        RIGHT_2(29) 
#define     TANK3_LEFT_0        RIGHT_2(30)   
#define     TANK3_LEFT_1        RIGHT_2(31) 

//�ӵ�����
#define     SP_BULLET_NUM		8
#define     SP_BULLET_UP		0xFD
#define     SP_BULLET_DOWN		0xFC
#define     SP_BULLET_RIGHT		0xFE
#define     SP_BULLET_LEFT		0xFF
#define     SEND_BULLET			0x10
#define     CLR_SEND_BULLET	    0xEF
#define     SPACE        		0xFB

//��������
#define     TANK				0x30
#define     BRICK  				0x0F
#define     TREE				0x22
#define     STEEL				0x10
#define     WALL				0x11
#define     WATER          		0x12
#define     ICE					0x21
#define     HOME0				0xC8
#define     HOME1				0xC9
#define     HOME2				0xCA
#define     HOME3				0xCB
//---------------------------------------------
//ȫ�ֱ�������
uint8 key,okey;	    //�ֱ�1
uint8 key2,okey2;	//�ֱ�2
uint8 x=80,y=138;  //start (80,138)	about (80,160)
uint8 pro_state=PRO_START; //����Ľ���״̬
uint8 time_ms=0;//����
uint8 stage_num=1;//�ؿ���
SPRITE SpTank[SP_TANK_NUM]; //�����̹����
SPRITE SpBullet[SP_TANK_NUM]; //������ӵ���
uint8  bullet_o_dir[SP_TANK_NUM];
uint8  tanklife[8]={0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82};
uint16 tank_time[8]={0,0,0,0,0,0,0,0};
uint8  pause_flag=0;
//---------------------------------------------
//��������
void run_start(void);   //��ʼ����
void run_game(void);	//��Ϸ����
void run_about(void);	//��Ϸ����
void run_stage(uint8 stage_num,uint8 life);//�ؿ���ʾ
uint8 check_road(uint8 *map,uint8 num,uint8 direction,uint8 x,uint8 y);//���ǰ���Ƿ�ͨ˳
void tank2map(uint8 *map,uint8 num,uint8 x,uint8 y);//��̹�˵����ݴ浽��ͼ��
void map_clr_tank(uint8 *map,uint8 num,uint8 x,uint8 y);//�ѵ�ͼ���̹���������
void slect_send(uint8 num);//����ѡ��
void run_pause(void);//��Ϸ��ͣ
//---------------------------------------------
//��ʼ����
//---------------------------------------------
void run_start(void)
{
    uint8 flag=1,n=0,i=0;
	uint8 sp_x[4]={0,0,8,8},sp_y[4]={0,8,0,8};


	//��ʼ������
	 x=START_X;
	 y=START_Y;	
	 time_ms=0;

	waitvblank();

	disable_graphics(); //����ʾ
	load_full_name_0((uint8*)strat_map); //���뿪ʼ�����ͼ����
	load_BG_palette((uint8*)strat_col);  //���뿪ʼ���汳����ɫ��
	load_SP_palette((uint8*)sp_col);     //���뾫���ɫ��  
	enable_graphics();  //����ʾ

	sound_init();	//������
	
	while( IsStart() )
	{  
		time_ms++;
		waitvblank();
        key = read_joy();
		if(downkey(button_SELECT))	  //ѡ��
		{	
			 if(flag)  //start
			 {
				 x=ABOUT_X;
				 y=ABOUT_Y;	
				 flag=0;
			 }
			 else  //about
			 {
				 x=START_X;
				 y=START_Y;	
				 flag=1;
			 }
			 slect_send(1);
		}
	    if(downkey(button_START))//ȷ��
		{
		     if(flag)  //start
			 {
				 pro_state=PRO_GAME;  //������Ϸ
				 okey=key;
				 continue;
			 }
			 else  //about
			 {
				 pro_state=PRO_ABOUT;//����about
				 okey=key;
				 continue;
			 }	
		} 

		//��ʾ����
		if(time_ms>5)
		{
		    time_ms=0;
			if(n==0)n=4;
			else n=0;
	    }
		for(i=0;i<4;i++)
		{ 		    
	    	putSP(i,x+sp_x[i],y+sp_y[i],TANK0_LEFT_0+n+i,0);
		}

		okey=key;  //ˢ��okey

	}
}

//---------------------------------------------
//��Ϸ��Ҫ����
//---------------------------------------------
void run_game(void)
{
    uint8 num=0,i=0,j=0,other_tank_flag=0;
	uint8 selct_tank=0;	//ѡ�еĿ����̷�����̹��
    uint8 selct_tank2=4;//ѡ�еĿ��ԻƷ�����̹��
    uint8 sp_x[4]={0,0,8,8},sp_y[4]={0,8,0,8},n=0,flag=0;
	uint8 tank_auto_dir[8]={0,0,0,0,0,0,0,0};
	uint8 auto_time[8]={0,0,0,0,0,0,0,0};
	uint8 sp_tile[SP_TANK_NUM]={   TANK0_DOWN_0, // 0
								   TANK1_DOWN_0, // 1
								   TANK2_DOWN_0, // 2
								   TANK3_DOWN_0, // 3
								   TANK0_UP_0,   // 4
								   TANK1_UP_0,   // 5
								   TANK2_UP_0,   // 6
								   TANK3_UP_0,   // 7
								 };


	run_stage(stage_num,0); //�ؿ�����ʾ 
	HideSP();//���ؾ���
	for(i=0;i<20;i++)
	{
		waitvblank();
	}
	
	//������ʼ��
	key=0;
	okey=0;
	time_ms=0;			
	for(i=0;i<SP_TANK_NUM;i++)
	{
	   if(i<(SP_TANK_NUM>>1))
	   {
		   SpTank[i].x=(5+i*6)*8;//x����	
		   SpTank[i].y=16;//y����
		   SpTank[i].tile=sp_tile[i];//Tile������
		   SpTank[i].attr=WHITE_TANK;//����:vhp000cc(��ֱ��ת ˮƽ��ת ��������Ȩ 000 ��ɫ�ĸ�2λ)
		   //�ӵ�
	   	   SpBullet[i].x=SpTank[i].x+3;
		   SpBullet[i].y=SpTank[i].y;
		   SpBullet[i].tile=SP_BULLET_DOWN;//Tile������
		   SpBullet[i].attr=WHITE_TANK;
		   SpBullet[i].dir|=DIR_DOWN;
		   bullet_o_dir[i]=DIR_DOWN;
	   }
	   else
	   {
		   SpTank[i].x=(5+(i-4)*6)*8;
		   SpTank[i].y=208;
		   SpTank[i].tile=sp_tile[i];
		   SpTank[i].attr=RED_TANK;	  		   
		   //�ӵ�
	   	   SpBullet[i].x=SpTank[i].x+3;
		   SpBullet[i].y=SpTank[i].y;
		   SpBullet[i].tile=SP_BULLET_UP;//Tile������
		   SpBullet[i].attr=WHITE_TANK;
		   SpBullet[i].dir|=DIR_UP;
		   bullet_o_dir[i]=DIR_UP;
	   }

	}

	SpTank[selct_tank].attr=GREEN_TANK;//ѡ��̹����ɫ�ĳ�ʼ��
    SpTank[selct_tank2].attr=YELLOW_TANK;//ѡ��̹����ɫ�ĳ�ʼ��
	
	waitvblank();

	disable_graphics(); //����ʾ
	load_full_name_0((uint8*)task_map); //����task�����ͼ����
	load_BG_palette((uint8*)task_col);  //����task���汳����ɫ��
	enable_graphics();  //����ʾ

	//��̹�˵����ݴ浽��ͼ��,�ⲽ����Ҫ
	for(i=0;i<SP_TANK_NUM;i++)
	{
    	tank2map((uint8*)task_map,(i<<2),SpTank[i].x,SpTank[i].y);
	}

	while( IsGame() )
	{
	    while(pause_flag)
		{
		   run_pause();
		}
	    time_ms++;
		//**************************************
		//�ֱ�1
	    key  = read_joy();
		if(presskey(button_UP))//��
		{
		    if(SpTank[selct_tank].tile!=RIGHT_2(selct_tank<<3))
			{
            	SpTank[selct_tank].tile=RIGHT_2(selct_tank<<3);
				SpTank[selct_tank].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank].dir|=DIR_UP;
		}
		else if(presskey(button_DOWN))//��
		{
		   	if(SpTank[selct_tank].tile!=RIGHT_2((selct_tank<<3)+4))
			{
            	SpTank[selct_tank].tile=RIGHT_2((selct_tank<<3)+4);
				SpTank[selct_tank].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank].dir|=DIR_DOWN;
		}
		else if(presskey(button_RIGHT))//��
		{
		   	if(SpTank[selct_tank].tile!=RIGHT_2((selct_tank<<3)+6))
			{
            	SpTank[selct_tank].tile=RIGHT_2((selct_tank<<3)+6);
				SpTank[selct_tank].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank].dir|=DIR_RIGHT;
		}
		else if(presskey(button_LEFT))//��
		{
		   	if(SpTank[selct_tank].tile!=RIGHT_2((selct_tank<<3)+2))
			{
            	SpTank[selct_tank].tile=RIGHT_2((selct_tank<<3)+2);
				SpTank[selct_tank].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank].dir|=DIR_LEFT;
		}

		if(downkey(button_SELECT))	  //ѡ��
	    {

		}
		if(downkey(button_START))
		{ 
			 pause_flag=1;
		}	  		    
    	if(presskey(button_A))	  //A ���ӵ�
		{
			if((tanklife[selct_tank]&0x7F)&&(SpBullet[selct_tank].dir&SEND_BULLET)==0)
			{  
			   slect_send(3);	
		       SpTank[selct_tank].dir|=SEND_BULLET;
			}
		}
		if(downkey(button_B))	  //B �л����Ƶ�̹��
		{
		    SpTank[selct_tank].attr=WHITE_TANK;
			selct_tank++;
			if(selct_tank>(SP_TANK_NUM>>1)-1)
			selct_tank=0;
			SpTank[selct_tank].attr=GREEN_TANK;
		}

		//**************************************
		//�ֱ�2
	    key2  = read_joy2();
		if(presskey2(button_UP))//��
		{
		    if(SpTank[selct_tank2].tile!=RIGHT_2((selct_tank2-4)<<3))
			{
            	SpTank[selct_tank2].tile=RIGHT_2((selct_tank2-4)<<3);
				SpTank[selct_tank2].dir|=DIR_CHANGE;
			}
		    SpTank[selct_tank2].dir|=DIR_UP;
		}
		else if(presskey2(button_DOWN))//��
		{
		   	if(SpTank[selct_tank2].tile!=RIGHT_2(((selct_tank2-4)<<3)+4))
			{
            	SpTank[selct_tank2].tile=RIGHT_2(((selct_tank2-4)<<3)+4);
				SpTank[selct_tank2].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank2].dir|=DIR_DOWN;
		}
		else if(presskey2(button_RIGHT))//��
		{
		   	if(SpTank[selct_tank2].tile!=RIGHT_2(((selct_tank2-4)<<3)+6))
			{
            	SpTank[selct_tank2].tile=RIGHT_2(((selct_tank2-4)<<3)+6);
				SpTank[selct_tank2].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank2].dir|=DIR_RIGHT;
		}
		else if(presskey2(button_LEFT))//��
		{
		   	if(SpTank[selct_tank2].tile!=RIGHT_2(((selct_tank2-4)<<3)+2))
			{
            	SpTank[selct_tank2].tile=RIGHT_2(((selct_tank2-4)<<3)+2);
				SpTank[selct_tank2].dir|=DIR_CHANGE;
			}
			SpTank[selct_tank2].dir|=DIR_LEFT;

		}

		if(downkey2(button_SELECT))	  //ѡ��
	    {
	     	slect_send(1);
		}	  		    
		if(presskey2(button_A))	  //A
		{
 			if((tanklife[selct_tank2]&0x7F)&&(SpBullet[selct_tank2].dir&SEND_BULLET)==0)
			{  
			   slect_send(3);	
		       SpTank[selct_tank2].dir|=SEND_BULLET;
			}
		}
		if(downkey2(button_B))	  //B
		{
		    SpTank[selct_tank2].attr=RED_TANK;
			selct_tank2++;
			if(selct_tank2>(SP_TANK_NUM-1))
			selct_tank2=(SP_TANK_NUM>>1);
			SpTank[selct_tank2].attr=YELLOW_TANK;
		}

		//****************************************

		for(i=0;i<8;i++)
		{	  
		      if((tanklife[i]&0x80)&&(i!=selct_tank)&&(i!=selct_tank2))
			  {	  
			      auto_time[i]++;
				  if( auto_time[i]>=AUTOTIME)
				  {
				     auto_time[i]=0;
				     tank_auto_dir[i]=rnd(40);
					 if((tanklife[i]&0x7F)&&(SpBullet[i].dir&SEND_BULLET)==0)
					 {  	
				        SpTank[i].dir|=SEND_BULLET;
				 	 }
				  }
				  if(tank_auto_dir[i]>=0&&tank_auto_dir[i]<=9)
				  {
				    if(SpTank[i].tile!=RIGHT_2((i%4)<<3))
					{
		            	SpTank[i].tile=RIGHT_2((i%4)<<3);
						SpTank[i].dir|=DIR_CHANGE;
					}
				     SpTank[i].dir|=DIR_UP;
				  }
				  else if(tank_auto_dir[i]>=10&&tank_auto_dir[i]<=19)
				  {
				    if(SpTank[i].tile!=RIGHT_2(((i%4)<<3)+4))
					{
		            	SpTank[i].tile=RIGHT_2(((i%4)<<3)+4);
						SpTank[i].dir|=DIR_CHANGE;
					}
				  	 SpTank[i].dir|=DIR_DOWN;
				  }
				  else if(tank_auto_dir[i]>=20&&tank_auto_dir[i]<=29)
				  {
				    if(SpTank[i].tile!=RIGHT_2(((i%4)<<3)+6))
					{
		            	SpTank[i].tile=RIGHT_2(((i%4)<<3)+6);
						SpTank[i].dir|=DIR_CHANGE;
					}
				  	 SpTank[i].dir|=DIR_RIGHT;
				  }
				  else if(tank_auto_dir[i]>=30&&tank_auto_dir[i]<=39)
				  {
				    if(SpTank[i].tile!=RIGHT_2(((i%4)<<3)+2))
					{
		            	SpTank[i].tile=RIGHT_2(((i%4)<<3)+2);
						SpTank[i].dir|=DIR_CHANGE;
					}
				  	  SpTank[i].dir|=DIR_LEFT;
				  }
			  }

			  if((SpTank[i].dir)||(SpBullet[i].dir&SEND_BULLET))
			  {
					//����ı�ʱ����Ϊ8��������
			  		if(SpTank[i].dir&DIR_CHANGE) 
					{
					   SpTank[i].dir&=DIR_CLR_CHANGE;	
					   bullet_o_dir[i]=(SpTank[i].dir&0x0f);
					   if(SpTank[i].x%8>4)
					   {
					   	  SpTank[i].x=SpTank[i].x-SpTank[i].x%8+8;
					   }
					   else
					   {
					   	  SpTank[i].x=SpTank[i].x-SpTank[i].x%8;
					   }
		
					   if(SpTank[i].y%8>4)
					   {
					   	  SpTank[i].y=SpTank[i].y-SpTank[i].y%8+8;
					   }
					   else
					   {
					   	  SpTank[i].y=SpTank[i].y-SpTank[i].y%8;
					   }
		
					}	
	                else if(SpTank[i].dir&SEND_BULLET)//���ӵ�����ȷ���ӵ��ĳ�ʼλ�úͷ���
					{
						 SpTank[i].dir&=CLR_SEND_BULLET;
						 SpBullet[i].dir=bullet_o_dir[i];
						 SpBullet[i].dir|=SEND_BULLET;
						 if(SpBullet[i].dir&DIR_UP)
						 {
						 	SpBullet[i].tile=SP_BULLET_UP;
							SpBullet[i].x=SpTank[i].x+3;
						    SpBullet[i].y=SpTank[i].y;
						 }
						 else if(SpBullet[i].dir&DIR_DOWN)
						 {
						 	SpBullet[i].tile=SP_BULLET_DOWN;
							SpBullet[i].x=SpTank[i].x+3;
						    SpBullet[i].y=SpTank[i].y;
						 }
						 else if(SpBullet[i].dir&DIR_RIGHT)
						 {
						 	SpBullet[i].tile=SP_BULLET_RIGHT;
						    SpBullet[i].x=SpTank[i].x;
						    SpBullet[i].y=SpTank[i].y+3;
						 }
						 else if(SpBullet[i].dir&DIR_LEFT)
						 {
						 	SpBullet[i].tile=SP_BULLET_LEFT;
							SpBullet[i].x=SpTank[i].x;
						    SpBullet[i].y=SpTank[i].y+3;
						 }
					} 

					//�ĸ������ϻ����ӵ��ж���
				    if((SpTank[i].dir&0x0f)||(SpBullet[i].dir&SEND_BULLET))
					{
    				    map_clr_tank((uint8*)task_map,(i<<2),SpTank[i].x,SpTank[i].y);//�ѵ�ͼ���̹���������		
						
						if(SpBullet[i].dir&SEND_BULLET)
						{
							//����ӵ�ǰ���Ƿ���Ŀ��
					    	if(check_road((uint8*)task_map,i|0x80,SpBullet[i].dir,SpBullet[i].x,SpBullet[i].y))		
					 		{
								if(SpBullet[i].dir&DIR_UP) SpBullet[i].y=SpBullet[i].y-BULLET_SPEED;
								else if(SpBullet[i].dir&DIR_DOWN) SpBullet[i].y=SpBullet[i].y+BULLET_SPEED;
								else if(SpBullet[i].dir&DIR_RIGHT) SpBullet[i].x=SpBullet[i].x+BULLET_SPEED;
								else if(SpBullet[i].dir&DIR_LEFT) SpBullet[i].x=SpBullet[i].x-BULLET_SPEED;
								putSP(32+i,SpBullet[i].x,SpBullet[i].y,SpBullet[i].tile,SpBullet[i].attr);
					 		}
					 		else
					 		{
								if(SpBullet[i].dir&DIR_DOWN)
								{
								   SpBullet[i].y=SpBullet[i].y+8;
								}
								else if(SpBullet[i].dir&DIR_RIGHT)
								{
								   SpBullet[i].x=SpBullet[i].x+8;
								}
								SpBullet[i].tile=SPACE;
								putSP(32+i,SpBullet[i].x,SpBullet[i].y,SpBullet[i].tile,SpBullet[i].attr);
								SpBullet[i].dir&=CLR_SEND_BULLET;

					 		}
						}

						//���̹��ǰ���Ƿ�ͨ˳
						if(SpTank[i].dir&0x0f)
						{
							if(check_road((uint8*)task_map,i,SpTank[i].dir,SpTank[i].x,SpTank[i].y))	
							{
								 if(SpTank[i].dir&DIR_UP)SpTank[i].y--;
								 else if(SpTank[i].dir&DIR_DOWN)SpTank[i].y++;
								 else if(SpTank[i].dir&DIR_RIGHT)SpTank[i].x++;
								 else if(SpTank[i].dir&DIR_LEFT)SpTank[i].x--;	
									
							} 
							else
							{
							    auto_time[i]=AUTOTIME;
							}
							SpTank[i].dir&=0xf0;//�巽���־
						}	
															
				 	    tank2map((uint8*)task_map,(i<<2),SpTank[i].x,SpTank[i].y);//��̹�˵����ݴ浽��ͼ��
					}
					
			   }
		}

		//��ʾ����
		if(time_ms>5)
		{
		    time_ms=0;
			if(n==0)n=4;
			else n=0;
	    } 
	    for(j=0;j<SP_TANK_NUM;j++)
		{
		    if(tanklife[j]&0x80)
			{
			    for(i=0;i<4;i++)
				{ 		    
			    	putSP((j<<2)+i,SpTank[j].x+sp_x[i],SpTank[j].y+sp_y[i],SpTank[j].tile+n+i,SpTank[j].attr);
				}
			}
			else 
			{
			    if(tank_time[j]==0)
				{	 
				   waitvblank();
				    if(tanklife[j]&0x7F)
					{
						tanklife[j]=(tanklife[j]-1)&0x7F;
						if(j<4)
						{
					    	putc_xy(VRAM_name_0,(0x1d+tanklife[j]),(0x04+j),WALL);
						}
						else
						{
						   	putc_xy(VRAM_name_0,(0x1d+tanklife[j]),(0x14+j),WALL);
						}
					    						
					}
					if(tanklife[j])
					{ 
					    SpTank[j].x=0x00;	
					    SpTank[j].y=(0x1c<<8);				      
					}
				    for(i=0;i<4;i++)
					{ 		    
				    	putSP((j<<2)+i,SpTank[j].x+sp_x[i],SpTank[j].y+sp_y[i],SPACE,SpTank[j].attr);
					}
					ES();
					tank_time[j]++;
				}
				else if(tank_time[j]<0xff)
				{
				    tank_time[j]++;
				}
				else if(tank_time[j]==0xff)
				{
                     if(tanklife[j])  
					 {  
						   if(j<4)
						   {
							   SpTank[j].x=(6+j*6)*8;	
							   SpTank[j].y=16;
						   }
						   else
						   {
							   SpTank[j].x=(6+(j-4)*6)*8;
							   SpTank[j].y=208;		   
						   }
						   SpTank[j].tile=sp_tile[j];
						   tank2map((uint8*)task_map,(j<<2),SpTank[j].x,SpTank[j].y);//��̹�˵����ݴ浽��ͼ��

						   tanklife[j]|=0x80;	  
					 } 
					   tank_time[j]=0;
				}	   							
			}
		} 
		okey=key;   //ˢ��okey
		okey2=key2; //ˢ��okey2
	}
}

//---------------------------------------------
//���ǰ���Ƿ�ͨ˳
//---------------------------------------------
//ͨ˳���� 1�����ϰ����� 0
uint8 check_road(uint8 *map,uint8 num,uint8 direction,uint8 x,uint8 y)
{
    uint8 i=0;
    uint8 sp_check_x[2]={0,0},sp_check_y[2]={0,0};
	uint8 value=0,bullet_flag=0;

	 //��Ӧ����ĳ�ʼ������
	 if(direction&DIR_UP)
	 {
	     sp_check_x[0]=0; sp_check_x[1]=8;
		 sp_check_y[0]=0; sp_check_y[1]=0; 
	 }
	 else if(direction&DIR_DOWN)
	 {
	     sp_check_x[0]=0; sp_check_x[1]=8;
		 sp_check_y[0]=16;sp_check_y[1]=16; 	 
	 }
	 else if(direction&DIR_RIGHT)
	 {
	     sp_check_x[0]=16; sp_check_x[1]=16;
		 sp_check_y[0]=0; sp_check_y[1]=8; 	 
	 }
	 else if(direction&DIR_LEFT)
	 {
	     sp_check_x[0]=0; sp_check_x[1]=0;
		 sp_check_y[0]=0; sp_check_y[1]=8; 	 
	 }

	 //�жϵ�ͼ�ϵĲ���Խ�����ϰ�
	 for(i=0;i<2;i++)
	 {
	    value=map[( (x+sp_check_x[i])>>3 )+( ((y+sp_check_y[i])>>3)<<5 )]; 
	   if(num&0x80)
	   {
			if(SpBullet[num&0x0f].dir&SEND_BULLET)
			{  
			   if(value==WALL||(value>=0x60&&value<=0x72))
			   {
			   	  return  0;
			   }
			   if(value>=HOME0&&value<=HOME3)
			   {
			      if(((num&0x0f)<4)&&((y+sp_check_y[i])>>3)>0x05)  //�±�
				  {
					   map[0x0e+(0x1a<<5)]=WALL;
					   map[0x0f+(0x1a<<5)]=WALL;
					   map[0x0e+(0x1b<<5)]=WALL;
					   map[0x0f+(0x1b<<5)]=WALL;
				 	   waitvblank();
					   putc_xy(VRAM_name_0,0x0e,0x1a,0xcc);
					   putc_xy(VRAM_name_0,0x0f,0x1a,0xce);
					   putc_xy(VRAM_name_0,0x0e,0x1b,0xcd);
					   putc_xy(VRAM_name_0,0x0f,0x1b,0xcf);
					   ES();
					   pro_state=PRO_GAMEOVER;  //������Ϸ
				   }
				   else	 if((num&0x0f)>4&&((y+sp_check_y[i])>>3)<0x05) //�ϱ�
				   {
					   map[0x0e+(0x02<<5)]=WALL;
					   map[0x0f+(0x02<<5)]=WALL;
					   map[0x0e+(0x03<<5)]=WALL;
					   map[0x0f+(0x03<<5)]=WALL;
				 	   waitvblank();
					   putc_xy(VRAM_name_0,0x0e,0x02,0xcc);
					   putc_xy(VRAM_name_0,0x0f,0x02,0xce);
					   putc_xy(VRAM_name_0,0x0e,0x03,0xcd);
					   putc_xy(VRAM_name_0,0x0f,0x03,0xcf);
					   ES();	
					   pro_state=PRO_GAMEOVER;  //������Ϸ		   
				   }
				   
				   bullet_flag=2;			   
			   }
			   if(value>=(TANK|0x00)&&value<=(TANK|0x07))
			   {
					if(((num&0x0f)<4&&((value&0x0F)>=4))||((num&0x0f)>=4&&((value&0x0F)<4)))
					{
						tanklife[value&0x0F]&=0x7F;	
						map_clr_tank((uint8*)task_map,((value&0x0F)<<2),SpTank[value&0x0F].x,SpTank[value&0x0F].y);//�ѵ�ͼ���̹���������
					    return 0;
					}			   
			   }
			   if( (value==BRICK)||(value==STEEL)||(value==TREE))
			   {
			      if(value==BRICK)
				  {
					   bullet_flag=2;
				  }
				  if(value==STEEL)
				  {
				       if((num&0x0f)%4==3)
					   {
					     bullet_flag=2;
					   }
					   else
					   {
					   	  return 0;
					   }				  
				  }
				  if(((num&0x0f)%4==2)&&(value==TREE))
				  {
				  	   bullet_flag=2;
				  }
				  if(bullet_flag==2)
				  {
	                   map[( (x+sp_check_x[i])>>3 )+( ((y+sp_check_y[i])>>3)<<5 )]=0;
					   waitvblank();
					   putc_xy(VRAM_name_0,( (x+sp_check_x[i])>>3 ),((y+sp_check_y[i])>>3),0);//������������赲
					   ES();				  
				  }
			   }
	           if((bullet_flag==2)&&(i==1))
			   {
			     bullet_flag=0;
			   	 return 0;
			   }
			}

		}
		else
		{
	    	if( (value>=(TANK|0x00)&&value<=(TANK|0x07))||(value==BRICK)||(value==WALL)||(value==STEEL)||(value==WATER)||(value>=HOME0&&value<=HOME3)||(value>=0x60&&value<=0x72) )
			{
				 return 0;
			}
		}
	 }

	 bullet_flag=0;
	 return	 1;
}

//---------------------------------------------
//��̹�˵����ݴ浽��ͼ��
//---------------------------------------------
void tank2map(uint8 *map,uint8 num,uint8 x,uint8 y)
{
       if(x%8>4)
	   {
	   	  x=x-x%8+8;
	   }
	   else
	   {
	   	  x=x-x%8;
	   }

	   if(y%8>4)
	   {
	   	  y=y-y%8+8;
	   }
	   else
	   {
	   	  y=y-y%8;
	   }
	   map[num] = map[(x>>3)+((y>>3)<<5)];
	   map[num+1] = map[(x>>3)+(((y+8)>>3)<<5)];
	   map[num+2] = map[((x+8)>>3)+((y>>3)<<5)];
	   map[num+3] = map[((x+8)>>3)+(((y+8)>>3)<<5)];

	   map[(x>>3)+((y>>3)<<5)] = (TANK|(num>>2));
	   map[(x>>3)+(((y+8)>>3)<<5 )] = (TANK|(num>>2));
	   map[((x+8)>>3)+((y>>3)<<5 )] = (TANK|(num>>2));
	   map[((x+8)>>3)+(((y+8)>>3)<<5 )] = (TANK|(num>>2));	

}
//---------------------------------------------
//�ѵ�ͼ���̹���������
//---------------------------------------------
void map_clr_tank(uint8 *map,uint8 num,uint8 x,uint8 y)
{
       if(x%8>4)
	   {
	   	  x=x-x%8+8;
	   }
	   else
	   {
	   	  x=x-x%8;
	   }

	   if(y%8>4)
	   {
	   	  y=y-y%8+8;
	   }
	   else
	   {
	   	  y=y-y%8;
	   }

	   map[(x>>3)+((y>>3)<<5)] = map[num];
	   map[(x>>3)+(((y+8)>>3)<<5 )] = map[num+1];
	   map[((x+8)>>3)+((y>>3)<<5 )] = map[num+2];
	   map[((x+8)>>3)+(((y+8)>>3)<<5 )] = map[num+3];	
}
//---------------------------------------------
//�ؿ���ʾ
//---------------------------------------------
void run_stage(uint8 stage_num,uint8 life)
{
	time_ms=0;

	waitvblank();
    address(PPU_ctrl_reg_1) = bin(	0,0,0,1,0,0,0,0); //����ʾ  
	address(PPU_ctrl_reg_2) = bin(	0,0,0,0,0,1,1,0);
	load_full_name_0((uint8*)stage_map); //����ؿ��׶λ����ͼ����
	load_BG_palette((uint8*)stage_col);  //����ؿ��׶λ��汳����ɫ��
    address(PPU_ctrl_reg_1) = bin(	1,0,0,1,0,0,0,0); //����ʾ  
	address(PPU_ctrl_reg_2) = bin(	0,0,0,0,1,1,1,0);

	gotoxy(18,13);
	cprintf("%u",stage_num);

	while(1)
	{
	    if(life)
		{
	    	time_ms++;
			if(time_ms>80)
			{
				break;
			}
		}

	    waitvblank();
	    key = read_joy();
		if(downkey(button_START))
		{
			life=1;
			slect_send(1);
			break;
		}
		okey=key;
	}

}
//---------------------------------------------
//����ѡ��
//---------------------------------------------
void slect_send(uint8 num)
{
   switch(num)
   {
   	  case 1:sound(sound_chn_0,0x8f,0xaa,0xaa,0x80);
			 break;
	  case 2:sound(sound_chn_0,0x1a,0x8a,0x3c,0x2a);		
	         break;
	  case 3:sound(sound_chn_0,0x89,0x89,0xef,0x03);		
	         break;
	  default:break;
   }
}
//---------------------------------------------
//ABOUT����
//---------------------------------------------
void run_about(void)
{

	time_ms=0;
	
	waitvblank();  

	HideSP();//���ؾ���

	disable_graphics(); //����ʾ
	load_full_name_0((uint8*)about_map); //����ؿ��׶λ����ͼ����
	load_BG_palette((uint8*)about_col);  //����ؿ��׶λ��汳����ɫ��
    address(PPU_ctrl_reg_1) = bin(	1,0,0,1,0,0,0,0); //����ʾ  
	address(PPU_ctrl_reg_2) = bin(	0,0,0,0,1,1,1,0);

	while( IsAbout() )
	{
	    time_ms++;
	    waitvblank();
	    key = read_joy();
		if(downkey(button_START))//ȷ��
		{
		    pro_state=PRO_START;  //���ؿ�ʼ����
		}
		okey=key;
	}
}
//---------------------------------------------
//��Ϸ��ͣ
//---------------------------------------------
void run_pause(void)
{
    waitvblank();
    key = read_joy();
	if(downkey(button_START))//ȷ��
	{
	    pause_flag=0;
	}
	okey=key;
}
//---------------------------------------------
//��Ϸ����
//---------------------------------------------
void run_gameover(void)
{
    int16 i=0,j=0;
	    uint8 sp_x[4]={0,0,8,8},sp_y[4]={0,8,0,8};
	key=0;
	okey=0;
	gotoxy(0x0b,0x0e);
	cprintf("%c%c%c%c%c%c%c%c",0x78,0x7a,0x7c,0x7d,0x79,0x7b,0x7d,0x7f); 
	for(i=0;i<1024;i++)
	{
		task_map[i]=task_map_back[i];
	}
	for(i=0;i<8;i++)
	{
		tanklife[i]=0x82;
		tank_time[i]=0;
	}
	waitvblank();
	for(j=0;j<8;j++)
	{
	    for(i=0;i<4;i++)
		{ 		    
	    	putSP((j<<2)+i,SpTank[j].x+sp_x[i],SpTank[j].y+sp_y[i],SPACE,SpTank[j].attr);	
		} 
		putSP(32+j,SpBullet[j].x,SpBullet[j].y,SPACE,SpBullet[j].attr);
	}
	ES();
    pause_flag=0;
    while( IsGameOver() )
    {
	    waitvblank();
	    key = read_joy();

		if(downkey(button_START))//ȷ��
		{
		    pro_state=PRO_START;  //������Ϸ
		}
		okey=key;
	}
}

//---------------------------------------------
//������
//---------------------------------------------
void main(void)
{

	while(1)
	{
		if( IsStart() )	 //��������
		{
		    run_start(); 
		}
		else if( IsGame() )//��Ϸ����
		{
			run_game();	 
		}
		else if( IsAbout() )//about����
		{
		    run_about(); 
		}
		else if( IsGameOver() ) //��Ϸ����
		{
		   run_gameover(); 
		}
	}

	while(1); //��ֹ����
}
