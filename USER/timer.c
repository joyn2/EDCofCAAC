/************************************************************
* �ļ�����: timer.c
* ����: �ܳ���
* �汾: 1.0
* ����: 2017/4/29
* ����: // 
* ��Ҫ�������书�� : // ��Ҫ�������书��
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/4/29 �����˴��ļ�˵��ע��
***********************************************************/

#include	"timer.h"
      enum 
{
	 ACTIVE,EXPIRED,STOPPED
} 
	Timer1_state=STOPPED,
	Timer2_state=STOPPED,
	Timer3_state=STOPPED,
	Timer4_state=STOPPED;
 static u16 Timer1_temp=0;
 static u16 Timer2_temp=0;
 static u16 Timer3_temp=0;
 static u16 Timer4_temp=0;

static struct  
{  u16 Timeout;
	u16 Hz;

} timer1_struct={0,0};
static struct  
{
  u16 Timeout;
	u16 Hz;
} timer2_struct={0,0};
static struct  
{
  u16 Timeout;
	u16 Hz;
} timer3_struct={0,0};
static struct  
{ u16 Timeout;
	u16 Hz;

} timer4_struct={0,0};
 


//���ö�ʱ���ķ���Ƶ��
void setTimerHertz(u8 whichTimer,u16 Hz)
{   				 
	   switch(whichTimer)
		 {
			
			 case Timer1:
			 {
				timer1_struct.Hz=Hz;  
			 };
			 break;
			 case Timer2:
			 {
				timer2_struct.Hz=Hz;  
			 };
			 break;
			 case Timer3:
			 {
				timer3_struct.Hz=Hz;  
			 };
			 break;
			 case Timer4:
			 {
				timer4_struct.Hz=Hz;  
			 };
			 break;
			 
		 }

	
}
u16 getTimerHertz(u8 whichTimer)
{
	 switch(whichTimer)
	 {
		
		 break;
		 case Timer1:
		 {
			  return timer1_struct.Hz;
		 };
		 break;
		 case Timer2:
		 {
			  return timer2_struct.Hz;
		 };
		 break;
		 case Timer3:
		 {
			  return timer3_struct.Hz;
		 };
		 break;
		 case Timer4:
		 {
			  return timer4_struct.Hz;
		 };
		 break;
		default: return 0;
	 }
}
//���ö�ʱ���Ķ�ʱʱ��
void setTimeout(u8 whichTimer,u16 time)
{ 	
	TIM_InitTypeDef		TIM_InitStructure;	
 
	switch(whichTimer)
	{

		case Timer1:
		{
			timer1_struct.Timeout=time;		
		  	TIM_InitStructure.TIM_Mode      = TIM_16BitAutoReload;	//ָ������ģʽ,   TIM_16BitAutoReload,TIM_16Bit,TIM_8BitAutoReload,TIM_16BitAutoReloadNoMask
			TIM_InitStructure.TIM_Polity    = PolityLow;			//ָ���ж����ȼ�, PolityHigh,PolityLow
			TIM_InitStructure.TIM_Interrupt = ENABLE;				//�ж��Ƿ�����,   ENABLE��DISABLE
			TIM_InitStructure.TIM_ClkSource = TIM_CLOCK_1T;			//ָ��ʱ��Դ,     TIM_CLOCK_1T,TIM_CLOCK_12T,TIM_CLOCK_Ext
			TIM_InitStructure.TIM_ClkOut    = DISABLE;				//�Ƿ������������, ENABLE��DISABLE
		  	TIM_InitStructure.TIM_Run       = DISABLE;				//�Ƿ��ʼ����������ʱ��, ENABLE��DISABLE
		  	TIM_InitStructure.TIM_Value     = 65536UL - (MAIN_Fosc / 1000);		//��ֵ,1ms
			Timer_Inilize(Timer1,&TIM_InitStructure);				//��ʼ��Timer0	  Timer0,Timer1,Timer
		};
		break;
		
	}
}
u16 getTimerout(u8 whichTimer)
{
	 switch(whichTimer)
	 {
		
		 case Timer1:
		 {
			  return timer1_struct.Timeout;
		 };
		 break;
		 case Timer2:
		 {
			  return timer2_struct.Timeout;
		 };
		 break;
		 case Timer3:
		 {
			  return timer3_struct.Timeout;
		 };
		 break;
		 case Timer4:
		 {
			  return timer4_struct.Timeout;
		 };
		 break;
		default: return 0;
	 }
	
}
//ͣ�ö�ʱ��
void stopTimer(u8 whichTimer)
{   switch(whichTimer)
	{  /*
		case Timer0:
		{
				TR0=0;
		};
		*/
		case Timer1:
		{
				TR1=0;
		 Timer1_state= STOPPED;

		};
		break;
	}
	 
}
//����ʱ����������δ�ﵽ��ʱʱ�䷵��1
bit isActiveTimer(u8 whichTimer)
{
	 switch(whichTimer)
	 {
	   case Timer1 :
	   {
		 return  Timer1_state == ACTIVE;

	   };
	   break;
	 }
}
//����ʱ�ﵽ�趨ʱ��ʱ����1
bit isExpiredTimer(u8 whichTimer)
{
	   switch(whichTimer)
	{
		case Timer1:
		{
				return  Timer1_state == EXPIRED;
		};
		break;
	}
			
	 
}
//����ʱ����ֹͣʱ����1
bit isStopped(u8 whichtimer)
{
	 switch(whichtimer)
	{
		case Timer1:
		{
				return  Timer1_state == STOPPED;
		};
		break;
	}
}

//��ʼ�����򿪶�ʱ������Ҫ�����úö�ʱʱ���Ƶ��
void restartTimer(u8 whichTimer)
{
	
	 switch(whichTimer)
	{
		case Timer1:
		{
				TR1=1;
		};
		break;
	}
	 
	 Timer1_state= ACTIVE;
	 

}
//����ʱ����ʱ�����󷵻�1�����Զ�����restart���������¶�ʱ
bit onRestartTimer(u8 whichTimer)
{
	  if (isExpiredTimer(whichTimer))
		{
			restartTimer(whichTimer);
			return TRUE;
		}
		else
		{
			return FALSE;
		} 
	
}


/********************* Timer1�жϺ���************************/
void Timer1_ISR (void) interrupt TIMER1_VECTOR
{

   if(Timer1_temp==timer1_struct.Timeout)
		 {
			  TR1=0;
			  Timer1_temp=0;
			  Timer1_state= EXPIRED;
		 }
		 else
		 {
			  Timer1_temp++;
		 }
		 

}

/********************* Timer2�жϺ���************************/
void Timer2_ISR (void) interrupt TIMER2_VECTOR
{
	
}

/********************* Timer3�жϺ���************************/
void timer3_int (void) interrupt TIMER3_VECTOR
{

}

/********************* Timer4�жϺ���************************/
void timer4_int (void) interrupt TIMER4_VECTOR
{

}

//========================================================================
// ����: u8	Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����: TIMx: �ṹ����,��ο�timer.h��Ķ���.
// ����: �ɹ�����0, �ղ�������1,���󷵻�2.
// �汾: V1.0, 2012-10-22
//========================================================================
u8 Timer_Inilize(u8 TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer4)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR0 = 0;		//ֹͣ����
		ET0 = 0;	//��ֹ�ж�
		PT0 = 0;	//�����ȼ��ж�
		TMOD &= 0xf0;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x80;	//12Tģʽ, 
		INT_CLKO &= ~0x01;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		TMOD |= TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x01;	//���ʱ��
		
		TH0 = (u8)(TIMx->TIM_Value >> 8);
		TL0 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TR1 = 0;	//ֹͣ����
		ET1 = 0;	//��ֹ�ж�
		PT1 = 0;	//�����ȼ��ж�
		TMOD &=  0x0f;	//��ʱģʽ, 16λ�Զ���װ
		AUXR &= ~0x40;	//12Tģʽ, 
		INT_CLKO &= ~0x02;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		TMOD |= (TIMx->TIM_Mode << 4);	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x02;	//���ʱ��
		
		TH1 = (u8)(TIMx->TIM_Value >> 8);
		TL1 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		AUXR &= ~0x1c;		//ֹͣ����, ��ʱģʽ, 12Tģʽ
		IE2  &= ~(1<<2);	//��ֹ�ж�
		INT_CLKO &= ~0x04;	//�����ʱ��
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	INT_CLKO |=  0x04;	//���ʱ��

		TH2 = (u8)(TIMx->TIM_Value >> 8);
		TL2 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer3)		//Timer3,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0xf0;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<5);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<5);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<1);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<1);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  1;	//���ʱ��

		TH3 = (u8)(TIMx->TIM_Value >> 8);
		TL3 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<3);	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer4)		//Timer4,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		T4T3M &= 0x0f;		//ֹͣ����, ��ʱģʽ, 12Tģʽ, �����ʱ��
		IE2  &= ~(1<<6);	//��ֹ�ж�
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<6);	//�����ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		T4T3M |=  (1<<5);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	T4T3M |=  (3<<5);	//����������Ƶ
		if(TIMx->TIM_ClkOut == ENABLE)	T4T3M |=  (1<<4);	//���ʱ��

		TH4 = (u8)(TIMx->TIM_Value >> 8);
		TL4 = (u8)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	T4T3M |=  (1<<7);	//��ʼ����
		return	0;		//�ɹ�
	}

	return 2;	//����
}

