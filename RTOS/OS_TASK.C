/********************************
*FileName:	 TASK_C
*Author	 :   JZHG1992
*Versions:	 V1.0
不可抢占式简单实时内核
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
*		 设置系统任务执行频度
*************************************/

#define TASK_DELAY0 TASK_CLOCK/100  // 任务0的执行频度,50hz
#define TASK_DELAY1 TASK_CLOCK/90  // 任务1的执行频度 ,10hz
#define TASK_DELAY2 TASK_CLOCK/30  // 任务2的执行频度
#define TASK_DELAY3 TASK_CLOCK/30    // 任务3的执行频度
#define TASK_DELAY4 TASK_CLOCK/30   // 任务4
#define TASK_DELAY5 TASK_CLOCK/8   // lcd刷新频率


//#define OS_DEBUG
/************************************
*		 任务0函数
*************************************/
void task0(void)
{
		Task_Delay[0] = TASK_DELAY0;  // 设置任务执行度
#ifdef OS_DEBUG
		PrintString1("task0 is on \n");  
#endif
   getAngle(PRESENT_ANGLE) ;
	 
//	
	
}
/************************************
*		 任务1函数
*************************************/

void task1( void )
{
	Task_Delay[1] = TASK_DELAY1;  // 设置任务执行度
 
#ifdef OS_DEBUG
		PrintString1("task1 is on \n");  
#endif
     setBoardWithAngleAndPID(70);

}
/************************************
*		 任务2函数
*************************************/

void task2( void )
{
	Task_Delay[2] = TASK_DELAY2;  // 设置任务执行度
	setAngle();
	/* 你的任务 */
#ifdef OS_DEBUG
		PrintString1("task2 is on \n");  
#endif

}
/************************************
*		 任务3函数
*************************************/

void task3( void )
{
	Task_Delay[3] = TASK_DELAY3;  // 设置任务执行度
#ifdef OS_DEBUG
		PrintString1("task3 is on \n");  
#endif
	buttonScan();

}

/************************************
*		 任务4函数
*************************************/

void task4( void )
{
	Task_Delay[4] = TASK_DELAY4;  // 设置任务执行度
  sendScopeData();
	/* 你的任务 */
#ifdef OS_DEBUG
		PrintString1("task4 is on \n");  
#endif
	
}

 void task5( void )
{
    	Task_Delay[5] = TASK_DELAY5;  // 设置任务执行度

	 	  LCD_UpdateAll();

}





/************************************
*		 获得任务指针
*        添加你的任务指针
*************************************/

void ( *const task[] )() = {  task0,task1,task2,task3,task4,task5 };

