/************************************************************
* �ļ�����: USER.C
* ����: �ܳ���
* �汾: 1.0
* ����: 2017/4/29
* ����: // �û���ĺ����ļ�
* ��Ҫ�������书�� : // ��Ҫ�������书��
  1.void setup(void )//��ʼ������
  2.void loop(void)//��ѭ���������൱��while��1��{}
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/4/29 �����˴��ļ�˵��ע��
***********************************************************/
#include "USER.h"
#include "../ANGLE/ANGLE.h"
#include "../MOTOR/MOTOR.h"
#include "../BUTTON/BUTTON.h"
#include "../DISPLAY/DataScope_DP.h"
#include "../DISPLAY/DISPLAY.H"
#include "../ANGLE/ANGLE.H"
#include "USART1.h"
#include "adc.h"
#include "STC15_PWM.H"
#include "UI.h"




//���е�����Ҫ���뵽user.h�н���Ӧ�ĺ궨�忪��
static u8 angle = 50, i = 0;//Ĭ�ϽǶ�
static float kp = 3.0f, ki = 0.02f, kd = 1.0f, leftMotorSpeed = 0.5f, rightMotorSpeed = 0.5f;
void setup(void)//��ʼ������
{
	UART1_init(UART1_BANDRATE);    //���ڳ�ʼ��
	GUI_Initialize(); //��ʼ��Һ��
	Button_config();//������ʼ��
	ADC_config(ANGLE_PIN, ANGLE_Speed);   //adc��ʼ��
	PID_config(kp, ki, kd);//pid�㷨��ʼ��	
	setMenu_MAXandMIN(7, 1);//�˵�����,�����Ϊ6
	PWM_config(PWM_2);//pwm��ʼ��
	PWM_config(PWM_4);
	PWM_period(5000);
	PWM_duty(PWM_2, 0.5f); //Ĭ��ռ�ձ�0.5f
	PWM_duty(PWM_4, 0.5f);
	EA = 1;  //���жϿ���	
	setPID_data(SET_ANGLE, 70);
	uiDraw();

}
/*************  ����1��ʼ������ *****************/
/*************************************************
* ��������: void    UART1_init(unsigned long BandRate)
* ����: ����1��ʼ������
* ����: unsigned long BandRate �����ڵĲ����ʣ�������ֵ�����ĸ"L"����ֹ������
* ���: ���ô˺����ᷢ��һ�β������ �� STC15w4k58s4 UART1 is open ��
* ����ֵ: ��
* ����˵��: ��
*************************************************/
void    UART1_init(unsigned long BandRate)
{
	COMx_InitDefine     COMx_InitStructure;           
	COMx_InitStructure.UART_Mode = UART_8bit_BRTx;    
	COMx_InitStructure.UART_BRT_Use = BRT_Timer2;     
	COMx_InitStructure.UART_BaudRate = BandRate;      
	COMx_InitStructure.UART_RxEnable = ENABLE;        
	COMx_InitStructure.BaudRateDouble = DISABLE;      
	COMx_InitStructure.UART_Interrupt = ENABLE;       
	COMx_InitStructure.UART_Polity = PolityHigh;      
	COMx_InitStructure.UART_P_SW = UART1_SW_P30_P31;  
	COMx_InitStructure.UART_RXD_TXD_Short = DISABLE;  
	USART_Configuration(USART1, &COMx_InitStructure); 
//    PrintString1("STC15w4k58s4 UART1 is open \r\n");   //���ڲ���
}

//����ʾ�������ݷ��ͺ���
void sendScopeData(void)
{
	u8 a; //
	u8 Send_Count;

	DataScope_Get_Channel_Data(getPID_data(ERR), 1);  //�������
	DataScope_Get_Channel_Data(getPID_data(OUTPUT) + getPID_data(SET_ANGLE), 2);  //ʵ���������
	DataScope_Get_Channel_Data(getPID_data(INTEGRAL), 3);  //��������
	DataScope_Get_Channel_Data(getPID_data(SET_ANGLE), 4);  //�趨�Ƕ�
	DataScope_Get_Channel_Data(getAngle(PRESENT_ANGLE), 5);  //ʵ�ʽǶ�

	Send_Count = DataScope_Data_Generate(5); //
	for (a = 0; a < Send_Count; a++)
	{
		TX1_write2buff(DataScope_OutPut_Buffer[a]); //����һͨ�����ݵ�����ʾ����
	}

}