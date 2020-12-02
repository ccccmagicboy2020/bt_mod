#define ALLOCATE_EXTERN
#include "HC89S003F4.h"
//#include "Mcu_api.h"
#include "bluetooth.h"

//#define V11
#define V12


#define  VERSION  0X21

#define  TH_LOW		30000
#define  TH_HIGH	4000000

#define  TH_DEF		40000
	
//��������ֵƫ�Χ
#define  MAX_DELTA0  20000
#define  MAX_DELTA1  60000

#define  MAX_DELAY	1800
//�����ʱ����

//�й�����-30��Ӧ8LUX���ҵ�ADֵ,����Ϊ255��ʾ�����й�
#define  LIGHT_TH0 255
//30

//һ���������Ϊ0.25��
//#define DELAY_NUM 20


//#define LIGHT_ON P0_6=0
//#define LIGHT_OFF P0_6=1

//void Delay_2us(u16 Cnt);		//��ʱ����

// bit Timer1_FLAG;
// bit Time_10mS_FLAG;
// bit Time_100mS_FLAG;
// bit Time_200mS_FLAG;
// bit Time_500mS_FLAG;
// bit Time_1S_FLAG;
// bit Time_10S_FLAG;
// bit Time_1Min_FLAG;
// bit Time_1H_FLAG;

volatile ulong Timer_Counter=0;

 //u8 Uart1_RX_Buff[10] = {0};					 //���ڴ��UART1��������
 //u8 Uart1_RX_Cnt = 0;								 //UART1���ռ���
 //u8 Uart1_TX_Buff[20] = {0};					 //���ڴ��UART1��������
 //u8 Uart1_TX_Cnt = 0;								 //UART1���ͼ���
 
// u16 AN1_Data = 0;
// u16 AN7_Data = 0;
// u8 Uart_Cnt = 0;


	u8 xdata SUM1_counter=0,SUM1_num=64,SUM0_num=12;
	ulong xdata SUM1=0,SUM0=0,SUM=0,ALL_SUM1=0,SUM10=0,SUM16=0,SUM01,SUM2;
	u16   xdata times=0,start_times=1;
	ulong  xdata TH,MAX_DELTA;
	u8  xdata alarm_times=0,stop_times=0;

	uint  xdata average,LIGHT=0,LIGHT_off=0;
	u8  xdata light_ad,light_ad0,check_light_times=8,calc_average_times=0,check_sum,send_byte;
	u8  xdata LIGHT_TH;
	u16  xdata DELAY_NUM;
	u8 xdata lowlightDELAY_NUM;
	u8  xdata RXnum=0;
	u8 while_1flag = 0;
	u8 while_2flag = 0;
	u8 xdata  SWITCHflag = 0;
	u8 xdata  SWITCHflag2 = 0;
	
	u8 xdata  SWITCHfXBR = 1;
 	u8      xdata lightvalue = 10;
	u8 xdata switchcnt = 0;
	u8 xdata slowchcnt = 10;
	 u8 xdata resetbtcnt = 0;
	 u8 xdata XRBoffbrightvalue = 0;
	 volatile u16 xdata lowlight1mincount = 0;
	 volatile u8 xdata  lowlight1minflag =0;
	volatile u16 idata light1scount  = 0;
	volatile u16 idata light1sflag = 0;
	 u8 xdata addr = 0;
	 u8 xdata devgroup = 0;
	 u8 xdata addrend=0;
	 u16 idata groupaddr[8] = {0};
	 u8 idata check_group_flag = 0;
	 u8 idata check_group_count = 0;
	 u8 idata Linkage_flag  =0;
	 u8 idata Light_on_flag = 0;
	 u8 idata Light_on_flagpre = 0;
	 u8 xdata Alldaybrightflag = 0;
	 u8 idata devicemode = 0;
	 volatile u16 idata Exit_network_ontmincount = 0;
	 volatile u8 idata Exit_network_ontminflag = 0;
	 volatile u8 idata Exit_network_controlflag = 0;
	 u8 idata LEDstate = 0;
	 bit idata ledFlashing = 0;
	 /*
	 u8 idata groupaddr2 = 0;
	 u8 idata groupaddr3 = 0;
	 u8 idata groupaddr4 = 0;
	 u8 idata groupaddr5 = 0;
	 u8 idata groupaddr6 = 0;
	 u8 idata groupaddr7 = 0;
	 u8 idata groupaddr8 = 0;
	 */
 unsigned char PWM3init(unsigned char ab);
void Flash_EraseBlock(unsigned int fui_Address);//��������
//void FLASH_WriteData(unsigned char fui_Address, unsigned int fuc_SaveData);//д��һ������
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address);
//void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//д�����ⳤ������
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//��ȡ���ⳤ������

//unsigned char guc_Write_a[5] = {0};	//д������
unsigned char xdata guc_Read_a[11] = {0x00};			//���ڴ�Ŷ�ȡ������
unsigned char xdata guc_Read_a1[1] = {0x00};			//���ڴ�Ŷ�ȡ������
// unsigned char guc_Uartflag = 0;					  //���ͱ�־λ
// unsigned char guc_Uartcnt = 0;					  //���ͼ���
// unsigned char guc_Uartbuf_a[2] = {0x00};	//��������

void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//��ȡ����
}

void Delay_us(uint q)
{
	uint j;
	for(j=0;j<q;j++)
	{
			;
	}
}

void Delay_ms(uint t)
{
	Timer_Counter=0;
	while(Timer_Counter<t)
	{
		WDTC |= 0x10;		//�忴�Ź�
	}
	
}

void Delay_us_1(uint q1)
{
	uint j;
	for(j=0;j<q1;j++)
	{
			;
	}
}



// void Delay_ms(uint t)
// {
// 	for(;t>0;t--)
// 	{
// 		Delay_us_1(1000);
// 		WDTC |= 0x10;		//�忴�Ź�
// 	}
// }

/***************************************************************************************
  * @˵��  	ϵͳ��ʼ������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void InitSYS()
{
	/********************************ϵͳƵ�ʳ�ʼ��***************************************/
	
	CLKSWR = 0x51;						         //ѡ���ڲ���ƵRCΪϵͳʱ�ӣ��ڲ���ƵRC 2��Ƶ��Fosc=16MHz
	CLKDIV = 0x01;						         //Fosc 1��Ƶ�õ�Fcpu��Fcpu=16MHz 
	FREQ_CLK = 0x10;									 //IAPƵ��
	
	/**********************************��ѹ��λ��ʼ��**************************************/
	
//	BORC = 0xC0;											 //ʹ�ܵ�ѹ��λ1.8V��������ʹ��
//	BORDBC = 0x01;										 //����ʱ��BORDBC*8TCPU+2TCPU
	
	/***********************************���ſڳ�ʼ��***************************************/
	WDTC = 0x5F;											 //����WDT��λ������ģʽ�½�ֹWDT��ѡ��1024��Ƶ���ڲ���Ƶʱ��44K��
	WDTCCR = 0X20;	//0X20/44	=0.73��						//0xFF;	 //���ʱ��Լ6��
	//�������ʱ��=��WDT��Ƶϵ��*��WDTCCR+1����/�ڲ���ƵRCƵ��
}

/***************************************************************************************
  * @˵��  	��ʱ����ʼ������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void Timer_Init()
{
	/**********************************TIM1���ó�ʼ��**************************************/
	TCON1 = 0x00;						  //T1��ʱ��ʱ��ΪFosc
	TMOD = 0x01;						  //T1-16λ��װ�ض�ʱ��/������,T0-16λ��ʱ��

	//Tim1����ʱ�� 	= (65536 - 0xFACB) * (1 / (Fosc /Timer��Ƶϵ��))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//��ʱ1ms
	//���Ƴ�ֵ 	= 65536 - ((1/1000) / (1/(Fosc / Timer��Ƶϵ��)))
	//		   	= 65536 - ((1/1000) / (1/(16000000 / 12)))
	//			= 65536 - 1333
	//			= 0xFACB
	
	TH1 = 0xFA;
	TL1 = 0xCB;
	IE |= 0x08;							  //��T1�ж�
	TCON |= 0x40;						  //ʹ��T1
    
	
		
	TH0 = 0xCB;
	TL0 = 0xEB;							  //T0��ʱʱ��10ms
	
	TCON |= 0x10;						  //ʹ��T0
}

/***************************************************************************************
  * @˵��  	UART1��ʼ������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void UART1_Init()
{
	/**********************************UART���ó�ʼ��**************************************/
	P2M0 = P2M0&0xF0|0x08;				      //P20����Ϊ�������
	P0M2 = P0M2&0xF0|0x02;				      //P04����Ϊ��������
	P0_4 = 1;
	TXD_MAP = 0x20;						          //TXDӳ��P20
	RXD_MAP = 0x04;						          //RXDӳ��P04		
	T4CON = 0x06;						            //T4����ģʽ��UART1�����ʷ�����
	
	//�����ʼ���
	//������ = 1/16 * (T4ʱ��ԴƵ�� / ��ʱ��4Ԥ��Ƶ��) / (65536 - 0xFF98)
	//       = 1/16 * ((16000000 / 1) / 104)
	//		 = 9615.38(���0.16%)

	//������9600
	//���Ƴ�ֵ = (65536 - ((T4ʱ��ԴƵ�� / ��ʱ��4Ԥ��Ƶ��) * (1 / 16)) / ������)
	//		   = (65536 - (16000000 * (1 / 16) / 9600))
	//		   = (65536 - 104.167)
	//         = FF98
	//0xFF98->9600
	//0xFFCC->19200
	//0xFFEF->57600
	
	
  TH4 = 0xFF;
	TL4 = 0x98;	//������9600		//0xEE;				//������56000
	SCON2 = 0x02;						             //8λUART�������ʿɱ�
	SCON = 0x10;					               //�������н���
	IE |= 0X10;							             //ʹ�ܴ����ж�
	//EA = 1;							              	 //ʹ�����ж�
}

/***************************************************************************************
  * @˵��  	ADC��ʼ������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void ADC_Init()
{
	
	ADCC0 |= 0x03;						//�ο�ԴΪ�ڲ�2V
	ADCC0 |= 0x80;						  //��ADCת����Դ
	Delay_us(20);					 	//��ʱ20us��ȷ��ADCϵͳ�ȶ�
	ADCC1 = 0x01;						  //ѡ���ⲿͨ��1
	ADCC2 = 0x4b;					//8��Ƶ	  //ת�����12λ���ݣ������Ҷ��룬ADCʱ��16��Ƶ-1MHZ//0X4B-8��Ƶ//0X49-4��Ƶ
}

/***************************************************************************************
  * @˵��  	IO�ڳ�ʼ������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void GPIO_Init()
{
	//P0M0�ָ�4λ���4λ����4λ����P00�����������4λ����P01��������������Դ�����
	//P0M1��4����P03����4����P02
	//P1M2��4����P15����4����P14
	
// 	P0M0 = P0M0&0xF0|0x08;		      //P00����Ϊ�������
// 	P0M0 = P0M0&0x0F|0x30;				  //P01����Ϊģ������
// 	P0M3 = P0M3&0x0F|0x30;				  //P07����Ϊģ������
// 	P0M3 = P0M3&0xF0|0x08;		      //P06����Ϊ�������
	
	#ifdef V11
	
	P0M0 = P0M0&0xF0|0x08;		      //P00����Ϊ�������
	
	P0M0 = P0M0&0x0F|0x30;				  //P01����Ϊģ������
	//P0M3 = P0M3&0x0F|0x30;				  //P07����Ϊģ������
//	P0M0 = P0M0&0x0F|0x80;		      //P01����Ϊ�������
	
	P0M2 = P0M2&0x0F|0x80;		      //P05����Ϊ�������
	
	P0M3 = P0M3&0xF0|0x03;			//P06����Ϊģ������  //|0x08;		      //P06����Ϊ�������
	
	P0M3 = P0M3&0x0F|0x20;				  //P07����Ϊ��������	
	
	#endif
	
	#ifdef V10
	
	P0M0 = P0M0&0xF0|0x08;		      //P00
	
	P0M0 = P0M0&0x0F|0x30;				  //P01
	P0M3 = P0M3&0x0F|0x30;				  //P07
//	P0M0 = P0M0&0x0F|0x80;		      //P01
	
	P0M3 = P0M3&0xF0|0x08;		      //P06
	
	#endif
	
	#ifdef V12
	
	P1M0 = P1M0&0xF0|0x08;		      //P10����Ϊ�������
	
	P0M0 = P0M0&0x0F|0x30;				  //P01����Ϊģ������
	
	P2M1 = P2M1&0xF0|0x03;					//P22����Ϊģ������ 
	
	//P0M3 = P0M3&0x0F|0x30;				  //P07����Ϊģ������
//	P0M0 = P0M0&0x0F|0x80;		      //P01����Ϊ�������
	
	//P0M2 = P0M2&0x0F|0x80;		      //P05����Ϊ�������
	
	//P0M3 = P0M3&0xF0|0x03;			//P06����Ϊģ������  //|0x08;		      //P06����Ϊ�������
	
//	P0M3 = P0M3&0x0F|0x20;				  //P07����Ϊ��������	
	
	#endif		
	
	
}

// u16 Read_ADC(u8 Channel)
// {
// 	u16 ADC_Temp;
// 	ADCC1 = Channel;						  //ѡ���ⲿͨ��1
//   ADCC0 |= 0x40;					//����ADCת��
// 	while(!(ADCC0&0x20));		//�ȴ�ADCת������
// 	ADCC0 &=~ 0x20;					//�����־λ
// 	ADC_Temp = ADCR;				//��ȡADC��ֵ
// 	return ADC_Temp;
// }

/***************************************************************************************
  * @˵��  	ϵͳʱ�Ӽ�������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
/*
void System_Time_Cnt(void)
{
    static u32 Timer1Count1 = 0;
    static u8 Timer1Count2 = 0;
    u32 Tampe = 1;
    if(Timer1_FLAG)              //1ms
    {
        Timer1_FLAG = 0;
        Timer1Count1 ++;
        Tampe = Timer1Count1 % 10;
        if(Tampe == 0)
            Time_10mS_FLAG = 1;
        Tampe = Timer1Count1 % 100;
        if(Tampe == 0)
            Time_100mS_FLAG = 1;
        Tampe = Timer1Count1 % 200;
        if(Tampe == 0)
            Time_200mS_FLAG = 1;
        Tampe = Timer1Count1 % 500;
        if(Tampe == 0)
            Time_500mS_FLAG = 1;
        Tampe = Timer1Count1 % 1000;
        if(Tampe == 0)
            Time_1S_FLAG = 1;
        Tampe = Timer1Count1 % 10000;
        if(Tampe == 0)
        {
            Time_10S_FLAG = 1;
            Timer1Count1 = 0;
            Timer1Count2 ++;
            Tampe = Timer1Count2 % 6;
            if(Tampe == 0)
                Time_1Min_FLAG = 1;
            Tampe = Timer1Count2 % 60;
            if(Tampe == 0)
            {
                Time_1H_FLAG = 1;
                Timer1Count2 = 0;
            }
        }
    }
}
*/

/***************************************************************************************
  * @˵��  	ϵͳ����������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/

/*
void System_Task(void)
{
    u8 temp;
		if(Time_10mS_FLAG)
    {
        Time_10mS_FLAG = 0;
        //User TASK
        
        
        //User TASK
        if(Time_100mS_FLAG)
        {
            Time_100mS_FLAG = 0;
            //User TASK

        
        
            //User TASK
        }
        if(Time_200mS_FLAG)
        {
            Time_200mS_FLAG = 0;
            //User TASK

        
        
            //User TASK
        }
        if(Time_500mS_FLAG)
        {
            Time_500mS_FLAG = 0;
            //User TASK
						AN1_Data = Read_ADC(0x01);
					
            //User TASK
        }
         if(Time_1S_FLAG)
        {
            Time_1S_FLAG = 0;
            //User TASK

						temp = 0xFF & (AN1_Data >> 8);
						SBUF = temp;
						while(!(SCON & 0x02));
						SCON &=~ 0x02;			           //��������жϱ�־λ
						temp = 0xFF & AN1_Data;
						SBUF = temp;
						while(!(SCON & 0x02));
						SCON &=~ 0x02;			           //��������жϱ�־λ
						P0_0 =~ P0_0;	
						//User TASK
            
        }
        if(Time_10S_FLAG)
        {
            Time_10S_FLAG = 0;
            //User TASK
            

            //User TASK
        }
        if(Time_1Min_FLAG)
        {
            Time_1Min_FLAG = 0;
            //User TASK
        
        
        
            //User TASK
        }
        if(Time_1H_FLAG)
        {
            Time_1H_FLAG = 0;
            //User TASK
        
        
        
            //User TASK
        }
    }
}
*/

void send_data(u8 d)
{
		SBUF = d;
		while(!(SCON & 0x02));
		SCON &=~ 0x02;
}

uchar read_ad(uchar ch)
{
	u8 i;
	uint  ad_sum;
	
//	switch (ch)
//	{
//		case 3:
//			ADC_P16_AN3;
//			break;
//		case 4:
//			ADC_P15_AN4;
//			break;
//		case 5:
//			ADC_P14_AN5;
//			break;
//	}
	
	
// 	if(ch==3)
// 	{
// 		ADC_P16_AN3;
// 	}
// 	else if(ch==4)
// 	{
// 		ADC_P15_AN4;
// 	}
	
	ADCC1 = ch;						  //ѡ���ⲿͨ��
  ADCC0 |= 0x40;					//����ADCת��
	while(!(ADCC0&0x20));		//�ȴ�ADCת������
	ADCC0 &=~ 0x20;					//�����־λ
	
	//ADC_Temp = ADCR;				//��ȡADC��ֵ	
	
// 	delay_ms(1);
// 	
// 	ADC_TG; 
	Delay_us(100);
	
	ad_sum=0;
	//ADC_INT_IF_CLR; //���жϱ�־λ
	
	
	for(i=0;i<16;i++)
	{
// 		ADC_TG; 
// 		while(ADC_IF==0){};
// 		//adc_data = ADC_DATA_RD();
// 			
// 		k=ADC_DH;
// 		k =k <<8;
// 		k+=ADC_DL;
// 			
// 		ADC_INT_IF_CLR; //���жϱ�־λ
// 		ad_sum+=k;
			

		ADCC0 |= 0x40;					//����ADCת��
		while(!(ADCC0&0x20));		//�ȴ�ADCת������
		ADCC0 &=~ 0x20;					//�����־λ
		ad_sum += ADCR;				//��ȡADC��ֵ
		
		Delay_us(20);
	}
	
	//ADC_P14_AN5;
	ADCC1 =1;
	i=ad_sum>>8;
	
	Delay_us(100);
	return(i);
	
}

void set_var(void)
{
	
	Flash_ReadArr(0X2f00,11,guc_Read_a);	//��ȡ��ַ0x2F00��������
	
	TH=guc_Read_a[0];
	TH<<=8;
	TH+=guc_Read_a[1];
	TH*=1000;
	if(TH<TH_LOW||TH>TH_HIGH)TH=TH_DEF;
	
		
	LIGHT_TH=guc_Read_a[2];

  if(LIGHT_TH==0)LIGHT_TH=LIGHT_TH0;
	else 
		if(LIGHT_TH==0XFE)LIGHT_TH=255;

	DELAY_NUM=guc_Read_a[3];
	DELAY_NUM<<=8;
	DELAY_NUM+=guc_Read_a[4];
	if(DELAY_NUM==0||DELAY_NUM>MAX_DELAY)DELAY_NUM=5;
	
	//DELAY_NUM<<=2;
	lightvalue=guc_Read_a[5];
	//if(lightvalue>100)lightvalue=10;
	//XRBoffbrightvalue = lightvalue;
	
	lowlightDELAY_NUM = guc_Read_a[6];
	if(lowlightDELAY_NUM==0||lowlightDELAY_NUM>255)lowlightDELAY_NUM=1;
	
	SWITCHfXBR = (~guc_Read_a[7])&0x01;

	
	XRBoffbrightvalue = guc_Read_a[8];

	devicemode = guc_Read_a[9]&0x01;

//	SWITCHflag2=  guc_Read_a[10];
	
//	addr = guc_Read_a[7];
//	
//	devgroup = guc_Read_a[8];

//	addrend = guc_Read_a[9];
	
	Flash_ReadArr(0X2f80,1,guc_Read_a1);	//��ȡ��ַ0x2F00��������
	resetbtcnt = guc_Read_a1[0];
}


void XBRHandle(void)
{
	u8 i,j;
	u16 k;
//		if(while_1flag==0)
//		send_data(0x55);
		//while(1)
		if(while_1flag==0)
		{
			//send_data(0x66);
// 				ADC_TG; 
// 				while(ADC_IF==0){};
// 				//adc_data = ADC_DATA_RD();
// 					
// 				k = ADC_DH<<8;
// 				//adc_data =adc_data <<8;
// 				k+= ADC_DL;
// 					
// 				ADC_INT_IF_CLR; //���жϱ�־λ

			ADCC0 |= 0x40;					//����ADCת��
			while(!(ADCC0&0x20));		//�ȴ�ADCת������
			ADCC0 &=~ 0x20;					//�����־λ
			k = ADCR;				//��ȡADC��ֵ
			
			times++;
			
			SUM+=k;

			//�����ź�ֵ��ֱ����ѹƫ��ֵ
			if(k>average){k-=average;}
			else {k=average-k;}
			SUM1+=k;

			if((times&0x1ff)==0)
			{
				if(LIGHT>0)	//????
				{
					
					//LIGHT++;
					
					if(slowchcnt<100)
					{
						slowchcnt = slowchcnt+2;//
						if(slowchcnt>100)
						{
							slowchcnt = 100;
						}
					}
					if(Exit_network_controlflag==0)
					{
						PWM3init(slowchcnt);
					}
				}
				else if(LIGHT_off ==1)//else if((SWITCHflag2==0)&&(LIGHT_off ==1))
				{
					if(slowchcnt>XRBoffbrightvalue)
					{
						if(slowchcnt>=2)slowchcnt-=2;
						if(slowchcnt<lightvalue)slowchcnt=XRBoffbrightvalue;
					}
					if(Exit_network_controlflag==0)
					{
						PWM3init(slowchcnt);
					}
				}
			}
			
			if(times>=8192)	//250ms		//12800)	//330ms
			{

				WDTC |= 0x10;		//�忴�Ź�
				
				times=0;

				calc_average_times++;
			
				SUM16+=SUM;
				
				if(calc_average_times>=8)	//ÿ2.5S���¼���һ��ֱ����ѹֵ
				{
					calc_average_times=0;
					
					SUM16>>=16;
					//SUM16/=96000;//102400;
					average+=SUM16;
					average/=2;
					SUM16=0;
				}
				
				if(check_light_times<8)	//2s	��ȡһ�θй�ADֵ
				{
					check_light_times++;
				}
				else
				{
					if(LIGHT==0)	
					{
						//light_ad=READ_LIGHT();
						light_ad=read_ad(10);

						if((light_ad<=(light_ad0+2))&&(light_ad0<=(light_ad+2)))
							light_ad=light_ad0;

						light_ad0=light_ad;

						check_light_times=0;
					}
				}

				if(SUM0==0)
				{
					SUM0=SUM1+5000;	
					if(start_times==0&&SUM0>1000000)SUM0=1000000;
				}

				if(SUM1_counter==0)
				{
					SUM10=SUM1;
					MAX_DELTA=1;//SUM10>>3;		
					//if(MAX_DELTA<MAX_DELTA0)MAX_DELTA=MAX_DELTA0;
				}
				
					if((SUM10<(SUM1+MAX_DELTA))&&(SUM1<(SUM10+MAX_DELTA)))//???????????
					{
						SUM1_counter++;
						ALL_SUM1+=SUM1;
						SUM10=ALL_SUM1/SUM1_counter;
						MAX_DELTA=SUM10>>3;
						if(MAX_DELTA<MAX_DELTA0)MAX_DELTA=MAX_DELTA0;
						if(MAX_DELTA>MAX_DELTA1)MAX_DELTA=MAX_DELTA1;
						
						if(SUM0>SUM10)
						{
							SUM=SUM0-SUM10;
							if(SUM>80000)SUM0_num=6;
							else if(SUM>40000)SUM0_num=9;
							else SUM0_num=12;
						}
						else
						{
							SUM0_num=12;
						}
						
						if((SUM1_counter>=SUM0_num)&&(SUM10<SUM0))
						{
							if(SUM1_num>16)	//???????????????
							{
								if(SUM0_num<=9)SUM0=SUM10;
								else if(SUM0>(SUM10+4000))
								{
									SUM0+=SUM10;
									SUM0/=2;
								}
								SUM1_counter=0;
								ALL_SUM1=0;
							}
						}

						else if(SUM1_counter>=SUM1_num)
						{
							
// 							if(SUM0>SUM10)
// 							{
// 								if(SUM1_num>16)SUM0=SUM10;	//???????????????
// 							}
// 							else 
								
							if(SUM10>(SUM0+4000))
							{
								SUM=SUM10-SUM0;

								if((SUM10<8000000)&&(SUM<400000))
		//????????????,???????????????100000?,???????
								{
									if(SUM1_num>16)	//????????????
									{
										SUM0+=SUM10;
										SUM0/=2;
									}
									else
									{
										if(SUM>300000)SUM1_num=16;
										else if(SUM>150000)SUM1_num=12;
										else SUM1_num=8;
										if(SUM1_counter>=SUM1_num)
										{
											SUM0+=SUM10;
											SUM0/=2;
										}
									}
								}
							}
// 							else if((LIGHT>0)&&(TH==TH_LOW))
// 							{
// 								SUM=SUM10-SUM0;	
// 								TH+=SUM;		//?????????????
// 							}

							if(SUM1_counter>=SUM1_num)
							{
								SUM1_counter=0;
								ALL_SUM1=0;
							}
						}
					}
					else
					{
						SUM1_counter=0;
						ALL_SUM1=0;
					}


// 				//send_byte=0x35;
// 				check_sum=0xFa;
 				//send_data(0xFa);

// 				send_byte=TH>>15;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				//k=TH;
// 				send_byte=TH>>10;
// 				check_sum+=send_byte;
// 				send_data(send_byte);
// 					
// 				send_byte=LIGHT_TH;
// 				check_sum+=send_byte;
// 				send_data(send_byte);					

// 				//send_byte=light_ad;
// 				check_sum+=light_ad;
// 				send_data(light_ad);

// 				send_byte=average>>4;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				send_byte=SUM0>>16;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				send_byte=SUM0>>8;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				send_byte=SUM1>>16;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				send_byte=SUM1>>8;
// 				check_sum+=send_byte;
// 				send_data(send_byte);

// 				check_sum+=1;
// 				send_data(check_sum);

				if(stop_times>0)	//
				{
					stop_times--;	
					if((SUM0>(SUM01+6000))&&(SUM1<(SUM01+15000)))SUM0=SUM01+6000;
				}
				else
				{
				
					if(start_times>0)
					{
						start_times--;
						
						if(start_times>0)	//???????????,???????250*88ms=22S?????????					
						{
							//start_times++;
/*
							if(SUM0>600000)
							{
								TH=10000;
							}
							else */
							if(SUM0>8000000)
							{
								TH=800000;
							}
							else
							{
								SUM=SUM0+TH;
								if(SUM>9000000)
								{
									TH=9000000-SUM0;
								}
								//if(TH<30000)TH=30000;
							}

						}
						else
						{
							//TH=TH_LOW;
							//start_times=0;
//							EA=0;
//							set_var();
//							EA=1;
						}

					}

					if(SUM1>(SUM0+TH))
					{
						//SUM=SUM1-SUM0;

					//	if(SUM>TH)
					//	{
							if((light_ad<=LIGHT_TH)||(start_times>0))
							{
//								send_data(0xaa);

								
								//if(alarm_times<2)
								//{
								//	alarm_times++;
							//	  }
								//if(alarm_times>=2)	//??????????????
								{
									if(LIGHT==0)SUM01=SUM0;
									LIGHT=1;
									if(Light_on_flag==0)
									{
										mcu_dp_enum_update(DPID_PIR_STATE,0);
									}
									Light_on_flag = 1;
									//PC3=0;
//									LIGHT_ON;
									//slowchcnt = slowchcnt+20;//
									//if(slowchcnt>100)
									//{
									//	slowchcnt = 100;
									//}
									//PWM3init(slowchcnt);
									//P0_6=0;
//									send_data(0xaa);
//									send_data((TH/1000)>>8);
//									send_data((TH/1000)&0xff);
//									send_data(LIGHT_TH);
//									send_data(DELAY_NUM>>10);
//									send_data(DELAY_NUM>>2);		//������
//									send_data(slowchcnt);
//									send_data(0xaa);	
									//send_data(0xdd);

									SUM1_num=8;
									LIGHT_off=0;
									light1scount=0;
									light1sflag=0;
									//mcu_dp_enum_update(DPID_PIR_STATE,0);
	//								send_data(0xaa);

								}
							}
					
						}

				}

				SUM2=SUM1;
// 									send_data((TH/1000)>>8);
// 									send_data((TH/1000)&0xff);				
				//send_data(average>>4);
				
//				send_data(light_ad);
//				send_data(SUM0>>16);
//				send_data(SUM0>>8);
//				send_data(SUM2>>16);
//				send_data(SUM2>>8);			//20200927	������				
				
				SUM=0;
				SUM1=0;
				
				if(LIGHT>0)	//????
				{
					
					//LIGHT++;
					
// 					slowchcnt = slowchcnt+5;//
// 					if(slowchcnt>=100)
// 					{
// 						slowchcnt = 100;
// 					}
// 					PWM3init(slowchcnt);
					
					if(LIGHT>DELAY_NUM)
					{
						LIGHT=0;
						while_1flag=1;
						if(Light_on_flag==1)
						{
							mcu_dp_enum_update(DPID_PIR_STATE,1);
						}
						Light_on_flag=0;
						Light_on_flagpre=0;
						//while_2flag = 0;
						//break;
					}
				}
				
				
			}


		}
		else
		{
				//mcu_dp_enum_update(DPID_PIR_STATE,1);
				//mcu_dp_bool_update(DPID_PIR_STATE,Light_on_flag);
				LIGHT_off = 1;
				while_1flag=0;
				//if(while_2flag==0)
				//{
				//	while_2flag = 1;
//					send_data(0x55);
				//}
				//PC3=1;
//				LIGHT_OFF;
				//slowchcnt = lightvalue;
				//PWM3init(lightvalue);
				lowlight1mincount = 0;
				lowlight1minflag = 0;
				
			
				//P0_6=1;
				//send_data(0x55);
				Delay_ms(250);


				
		// 		SUM=0;
		// 		SUM1=0;
		// 		times=0;
				
				SUM16=0;
				calc_average_times=0;
				SUM1_num=64;
				
				stop_times=2;
				//if(start_times==0)TH=TH_LOW;
				check_light_times=6;
				
				SUM1_counter=0;
				ALL_SUM1=0;

		//		send_data(0xdd);
		//		send_data(0xdd);
		}

}


void wait1(void)
{
	u8 i,j;

	//�ȴ�ֱ����ѹ�ȶ�
	j=0;
	while(1)
	{
	  SUM=0;
		
		
// 	  for(i=0;i<4;i++)	//0.52s
// 	  {
// 	  	for(t=0;t<8192;t++)	//0.13s
// 	  	{

// 				ADCC0 |= 0x40;					//����ADCת��
// 				while(!(ADCC0&0x20));		//�ȴ�ADCת������
// 				ADCC0 &=~ 0x20;					//�����־λ
// 				k = ADCR;				//��ȡADC��ֵ
// 				
// 				SUM+=k;
// 	
// 	  	}
// 			
// 			WDTC |= 0x10;		//�忴�Ź�
			

	  	for(i=0;i<128;i++)	//
	  	{

				ADCC0 |= 0x40;					//����ADCת��
				while(!(ADCC0&0x20));		//�ȴ�ADCת������
				ADCC0 &=~ 0x20;					//�����־λ
				//k = ADCR;				//��ȡADC��ֵ
				
				SUM+=ADCR;
				
	  	}

//���͸й�ADֵ
// 				send_byte=0xFA;
// 				check_sum=send_byte;
// 				send_data(send_byte);

// 				//send_byte=light_ad;
// 				check_sum+=light_ad;
// 				send_data(light_ad);

// 				check_sum+=light_ad;
// 				send_data(light_ad);
// 				
// 				check_sum+=1;
// 				send_data(check_sum);



	//}
		
		Delay_ms(400);
			

		
		//WDTC |= 0x10;		//�忴�Ź�

		i=SUM>>11;
		if((i>12)&&(i<141)&&(j>20))break;

		j++;

		if(j>80)break;	//??35????????????1.1V???????

	}
}
void wait2(void)
{
	u8 i,j;
	u16 k,t;

	SUM=0;


	  for(i=0;i<8;i++)
	  {
	  	for(t=0;t<8192;t++)	
	  	{
// 				ADC_TG; 
// 				while(ADC_IF==0){};
// 				//adc_data = ADC_DATA_RD();
// 					
// 				k = ADC_DH<<8;
// 				//adc_data =adc_data <<8;
// 				k+= ADC_DL;
// 					
// 				ADC_INT_IF_CLR; //���жϱ�־λ
		
				ADCC0 |= 0x40;					//����ADCת��
				while(!(ADCC0&0x20));		//�ȴ�ADCת������
				ADCC0 &=~ 0x20;					//�����־λ
				k = ADCR;				//��ȡADC��ֵ
				
				SUM+=k;
	
	  	}
			WDTC |= 0x10;		//�忴�Ź�

	  }

	  average=SUM>>16;


// 	light_ad=read_ad(10);
// 	light_ad0=light_ad;

// 	Delay_ms(4);	//4ms
}

unsigned char PWM3init(unsigned char ab)
{
	 float i11;
	unsigned char j11;
	i11=ab*255/100;
	j11=i11;
	#ifdef V11
/************************************PWM3��ʼ��****************************************/
	//P0M3 = P0M3&0xF0|0x08;		//P06����Ϊ�������
	PWM3_MAP = 0x05;					//PWM3ӳ��P05��
	
	#endif
	
	#ifdef V10
	PWM3_MAP = 0x06;					//PWM3ӳ��P05��
	
	#endif

	#ifdef V12
	PWM3_MAP = 0x10;					//PWM3ӳ��P10��
	
	#endif	
	
		//���ڼ��� 	= 0xFF / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0xFF /(16000000 / 4)			
	// 			= 255 /4000000
	//			= 63.75us		��15.69KHZ		

	PWM3P = 0xFF;						  //PWM����Ϊ0xFF
	//��Ч��ƽʱ����㣨��ռ�ձȣ� 	
	//			= 0x55 / (Fosc / PWM��Ƶϵ��)		��Fosc��ϵͳʱ�����õĲ��֣�
	//			= 0x55 /(16000000 / 4)			
	// 			= 85 /4000000
	//			= 21.25us		ռ�ձ�Ϊ 21.25 / 63.75 = 34%

	PWM3D = j11;						  //PWMռ�ձ�����
	PWM3C = 0x94; 						//ʹ��PWM3���ر��жϣ����������ʱ��16��Ƶ
}
void resetbt(void)
{
	send_data(0x55);
	send_data(0xAA);
	send_data(0X00);
	send_data(0X04);
	send_data(0X00);
	send_data(0X00);
	send_data(0X03);


}
void getbtaddr(void)
{
	send_data(0x55);
	send_data(0xAA);
	send_data(0X00);
	send_data(0XB4);
	send_data(0X00);
	send_data(0X00);
	send_data(0Xb3);

}

void start(void)
{
	PWM3init(0);
	Delay_ms(500);
	PWM3init(100);
	Delay_ms(500);
	PWM3init(50);
	Delay_ms(500);
	PWM3init(100);
	Delay_ms(500);
}
void Exit_network_control(void)
{
	 //send_data(0xe1);
	if(Exit_network_controlflag==1)
	{
	 //send_data(0xe2);
		if(Exit_network_ontminflag==1)
		{
	 //send_data(0xe3);	
			Exit_network_ontminflag = 0;
			switch(LEDstate)
			{
				case 0://��ѯ����״̬
						bt_work_state = 0;
						send_data(0x55);
						send_data(0xAA);
						send_data(0X00);
						send_data(0X02);
						send_data(0X00);
						send_data(0X00);
						send_data(0X01);
				send_data(0xe1);		
				//PWM3init(0);
					break;

				case 1://û������,����˸
				//PWM3init(100);
				//LEDstate=0;
				
						if(ledFlashing==0)
						{
							PWM3init(0);
						}
						else
						{
							PWM3init(100);
						}
						ledFlashing = ~ledFlashing;
						
				send_data(0xe2);
					break;
				case 2://�Ѿ�����
						Exit_network_controlflag  = 0;
						LEDstate = 0;	
				send_data(0xe3);		
					break;

				default:
					break;
					

			}


			
		}

	}

}

/***************************************************************************************
  * @˵��  	������
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void main()
{
	u8 i,j;
	bt_protocol_init();
	InitSYS();
	GPIO_Init();
//	LIGHT_ON;
	//P0_6=0;
	PWM3init(0);
	Timer_Init();
	UART1_Init();
	ADC_Init();

	LVDC = 0xAA;						  //LVD����2.4V,��ֹ�ж�
	//	����ʱ�� = 	(0xFF + 2) * 1/Fcpu
	//			 =	(0xFF + 2) / 16000000	����ǰ��CPUʱ�ӣ�
	//			 =	16.0625us
	LVDDBC = 0xFF;					  //��������ʱ��
	LVDC &=~ 0x08;			      //���LVD�жϱ�־λ 	
// 	
	EA=1;
	
	//Delay_ms(200);
	start();
	
//	LIGHT_ON;
	//PWM3init(100);
	SWITCHflag = 1;
	light_ad=read_ad(10);
	light_ad0=light_ad;
	
	EA=0;
	set_var();
	
	//for(i=0;i<5;i++)send_data(guc_Read_a[i]);
	
// 	TXdata[0]=VERSION;
// 	t=TH/1000;
// 	TXdata[1]=t>>8;
// 	TXdata[2]=t;
// 	TXdata[3]=LIGHT_TH;
// 	t=DELAY_NUM/4;
// 	TXdata[4]=t>>8;
// 	TXdata[5]=t;

// 	TXdata[6]=light_ad;

// 	for(i=0;i<7;i++)send_data(TXdata[i]);	
	resetbtcnt++;
	
	Flash_EraseBlock(0X2F80);
	Delay_us_1(10000);
	FLASH_WriteData(resetbtcnt,0X2F80);
	Delay_us_1(100);
	
	EA=1;
	slowchcnt = lightvalue;
	//Delay_ms(200);
	PWM3init(lightvalue);

	wait1();

	//slowchcnt = lightvalue;
	//Delay_ms(200);
	//PWM3init(lightvalue);
//	LIGHT_OFF;
	//P0_6=1;
	Delay_ms(300);
	
	wait2();

	SUM=0;
	while(1)
	{
		WDTC |= 0x10;		//�忴�Ź�
		if(resetbtcnt>=5)
		{
			Exit_network_controlflag = 1;
			resetbtcnt = 0;
			resetbt();
		}
		Exit_network_control();
		if(check_group_count <=2)//һ�ϵ���һ���ȡ3��Ⱥ���ַ
		{
			if(check_group_flag == 1)
			{
					check_group_flag = 0;
					check_group_count ++;
					getbtaddr();
			}

		}
		/*
		if(devicemode==0)//��Ӧģʽ
		{
			


		}
		else
		{


		}
		*/
		if(while_1flag==0)
		{
			if((times&0x1f)==0)
				bt_uart_service();
		}
		
		if(SWITCHfXBR==1)//�״￪
		{
			if(while_2flag==0)
			{
				while_1flag=0;

				while_2flag = 1;
				slowchcnt = XRBoffbrightvalue;

				
				SUM16=0;
				calc_average_times=0;
				SUM1_num=64;
				
				stop_times=2;
				//if(start_times==0)TH=TH_LOW;
				check_light_times=6;
				
				SUM1_counter=0;
				ALL_SUM1=0;
			}
			
			XBRHandle();
			if(Alldaybrightflag==0)
			{
				if(LIGHT_off>0)//�ص���ʱ
				{
					if(lowlightDELAY_NUM != 0)
					{
						if(lowlight1minflag==1)
						{
							lowlight1minflag = 0;
							LIGHT_off++;
							if(LIGHT_off>=lowlightDELAY_NUM)
							{
								LIGHT_off=0;
								if(Exit_network_controlflag==0)
								{
									PWM3init(0);
								}

							}
						}
					}
					else
					{
						lowlight1minflag = 0;
						LIGHT_off=0;
						if(Exit_network_controlflag==0)
						{
							PWM3init(0);
						}
					}
				}
			}
			if(LIGHT>0)//������ʱ
			{
				if(light1sflag==1)
				{
					light1sflag = 0;
					LIGHT++;
				}
			}

			//����
			
			//if(Linkage_flag==1)
			//{
				if(Light_on_flagpre!=Light_on_flag)
				{
					Light_on_flagpre = Light_on_flag;
					LIGHT = 1;
					/*
					for(i=0;i<8;i++)
					{
						if(groupaddr[i] != 0)
						{
							mcu_dp_bool_mesh_update(DPID_SWITCH_LED,SWITCHflag2,groupaddr[i]);
						}	
					}
					*/


				}

			//}	
			
			
		}
		else
		{//�״��
			while_2flag = 0;
			if(SWITCHflag2==0)//�ص�
			{
				if(Exit_network_controlflag==0)
				{
					PWM3init(0);
				}
			}
			else
			{//����
				if(Exit_network_controlflag==0)
				{
					PWM3init(lightvalue);
				}
				while_1flag=0;

				slowchcnt = lightvalue;
				//PWM3init(lightvalue);

				
				SUM16=0;
				calc_average_times=0;
				SUM1_num=64;
				
				stop_times=2;
				//if(start_times==0)TH=TH_LOW;
				check_light_times=6;
				
				SUM1_counter=0;
				ALL_SUM1=0;
				
			}
	
		
		}



		

	}	
	
// 	while(1)
// 	{
// 		System_Time_Cnt();
// 		System_Task();
// 		WDTC |= 0x10;              //�幷
// 	}

	
	
}

/***************************************************************************************
  * @˵��  	T1�жϷ�����
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
	//Timer1_FLAG = 1;		//1mS
	Timer_Counter++;

	lowlight1mincount++;
	if(lowlight1mincount>=60000)
	{
		lowlight1mincount = 0;
		lowlight1minflag = 1;
	}
	light1scount++;
	if(light1scount>=1000)
	{
		check_group_flag = 1;
		light1scount=0;
		light1sflag=1;
	}
	Exit_network_ontmincount++;
	if(Exit_network_ontmincount>=1000)
	{
	    Exit_network_ontmincount = 0;
		Exit_network_ontminflag = 1;
		

	}
	
}

/***************************************************************************************
  * @˵��  	UART1�жϷ�����
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/

void UART1_Rpt(void) interrupt UART1_VECTOR
{
	u8 i;
	//u16 t;
	
	if(SCON & 0x01)						            //�жϽ����жϱ�־λ
	{
			i=SBUF;
			uart_receive_input(i);
			SCON &=~ 0x01;					          //��������жϱ�־λ
			EA=1;
	}
}

void UART2_Rpt(void) interrupt UART2_VECTOR
{
}

// void Delay_2us(u16 Cnt)
// {
// 	while(Cnt--);	
// }

void Flash_EraseBlock(unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			  //���LVD�жϱ�־λ
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;		
	EA=0;
	IAP_CMD = 0xF00F;				//Flash����
	IAP_ADDR = fui_Address;	//д�������ַ
	IAP_CMD = 0xD22D;				//ѡ�������ʽ�� ��������
	IAP_CMD = 0xE11E; 			//������IAP_ADDRL&IAP_ADDRHָ��0xFF��ͬʱ�Զ�����
	//EA=1;
}

/**
  * @˵��  	д��һ���ֽ����ݵ�Flash����
  *         �ú�������Ե�ַ���룬���������IAP����Ӧ���ֲ�
  * @����  	fui_Address ��FLASH��ַ
  *	@����	  fucp_SaveData��д�������
  * @����ֵ ��
  * @ע		  д֮ǰ�����ȶԲ������������в���
  */
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			   //���LVD�жϱ�־λ
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;	
	EA=0;
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				   //Flash����
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				   //�ֽڱ��
	IAP_CMD=0xE11E;				   //����һ�β���
	//EA=1;
}

/**
  * @˵��  	д�����ⳤ�ȵ����ݵ�FLASH����
  *         �ú�������Ե�ַ���룬���������IAP����Ӧ���ֲ�
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	  fuc_Length �� д�����ݳ���
  *			    ȡֵ��Χ��0x00-0xFF
  *	@����  *fucp_SaveArr��д������ݴ��������׵�ַ
  * @����ֵ ��
  * @ע		  д֮ǰ�����ȶԲ������������в���
  */

// void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
// {
// 	unsigned char fui_i = 0;
// 	EA=0;
// 	for(fui_i=0;fui_i<fuc_Length;fui_i++)
// 	{
// 		FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
// 	}
// 	EA=1;
// }

/**
  * @˵��  	��FLASH�����ȡ���ⳤ�ȵ�����
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	  fuc_Length ����ȡ���ݳ���
  *			    ȡֵ��Χ��0x00-0xFF
  *	@����	 *fucp_SaveArr����ȡ���ݴ�ŵ������׵�ַ
  * @����ֵ ��
  * @ע		  ��
  */
