//   ������Ϣ�ļ�����ֵ���͵��ض���
//                                                       ���ߣ��� ��
/////////////////////////////////////////////////////////////////////////////

#ifndef __TYPES_H
#define __TYPES_H

#ifndef 	 TRUE
#define 	 TRUE	1
#endif
#ifndef      FALSE
#define 	 FALSE   0
#endif 
typedef unsigned char	 uint8;
typedef signed 	 char	 int8;
typedef unsigned short 	 uint16;
typedef signed 	 short   int16;
typedef unsigned int     uint32;
typedef signed   int 	 int32;
typedef float    		 fp32;
typedef double   		 fp64;

#define address(add) (*((uint8*)add)) //�ڴ�Ķ�д��

//�����ı������ɫ
#define textcolor(YS) address(0x2006) = 0x3F,\
                      address(0x2006) = 0x03,\
					  address(0x2007) = YS 
#endif //����types.h
//////////////////////////////////////////////////////////////////////////////////
