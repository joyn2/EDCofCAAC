/************************************************************
* 文件名称: MAIN.C
* 作者:周晨阳
* 版本 :v1.0
* 描述: 内部函数，无需改动
***********************************************************/

#include "../RTOS/OS.H"
#include "../USER/USER.H"
/*************************************************
* 函数名称: void main()
* 描述: user文件实现方法
*************************************************/

void main()
{   	
	 
   setup();//初始化函数
   OS_Timer0_Init();
   OS_Run();
}
