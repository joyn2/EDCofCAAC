/********************************
*FileName:	 TASK_C
*Author	 :   JZHG1992
*Versions:	 V1.0
������ռʽ��ʵʱ�ں�
*********************************/

#include "OS.H"
#include "../ANGLE/ANGLE.h"
#include "../BUTTON/BUTTON.h"
#include "../DISPLAY/DataScope_DP.h"
#include "../USER/USER.h"
#include "../MOTOR/MOTOR.h"
#include "../DISPLAY/DISPLAY.h"
#include "../GUI/font5_7.h"




/************************************
*		 ����ϵͳ����ִ��Ƶ��
*************************************/

#define TASK_DELAY0 TASK_CLOCK/100  // ����0��ִ��Ƶ��,50hz
#define TASK_DELAY1 TASK_CLOCK/90  // ����1��ִ��Ƶ�� ,10hz
#define TASK_DELAY2 TASK_CLOCK/30  // ����2��ִ��Ƶ��
#define TASK_DELAY3 TASK_CLOCK/30    // ����3��ִ��Ƶ��
#define TASK_DELAY4 TASK_CLOCK/30   // ����4��ִ��Ƶ��
#define TASK_DELAY5 TASK_CLOCK/8   // lcdˢ��Ƶ��


//#define OS_DEBUG
/************************************
*		 ����0����
*************************************/
void task0(void)
{
		Task_Delay[0] = TASK_DELAY0;  // ��������ִ�ж�
#ifdef OS_DEBUG
		PrintString1("task0 is on \n");  
#endif
   getAngle(PRESENT_ANGLE) ;
	 setBoardWithAngleAndPID(70);
//	
	
}
/************************************
*		 ����1����
*************************************/

void task1( void )
{
	Task_Delay[1] = TASK_DELAY1;  // ��������ִ�ж�
 
#ifdef OS_DEBUG
		PrintString1("task1 is on \n");  
#endif
     

}
/************************************
*		 ����2����
*************************************/

void task2( void )
{
	Task_Delay[2] = TASK_DELAY2;  // ��������ִ�ж�
	setAngle();
	/* ������� */
#ifdef OS_DEBUG
		PrintString1("task2 is on \n");  
#endif

}
/************************************
*		 ����3����
*************************************/

void task3( void )
{
	Task_Delay[3] = TASK_DELAY3;  // ��������ִ�ж�
#ifdef OS_DEBUG
		PrintString1("task3 is on \n");  
#endif
	buttonScan();

}

/************************************
*		 ����4����
*************************************/

void task4( void )
{
	Task_Delay[4] = TASK_DELAY4;  // ��������ִ�ж�
  sendScopeData();
	/* ������� */
#ifdef OS_DEBUG
		PrintString1("task4 is on \n");  
#endif
	
}

 void task5( void )
{
    	Task_Delay[5] = TASK_DELAY5;  // ��������ִ�ж�

	 	  LCD_UpdateAll();

}





/************************************
*		 �������ָ��
*        �����������ָ��
*************************************/

void ( *const task[] )() = {  task0,task1,task2,task3,task4,task5 };
