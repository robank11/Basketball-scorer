#include<reg51.h>//51��Ƭ��ͷ�ļ�
typedef unsigned char uchar;
typedef unsigned int  uint;
sbit K1=P3^2;//��������ʱ��ʼ/��ͣ
sbit K2=P3^3;//24s����ʱ���¿�ʼ
sbit K3=P1^3;//�Ҷ�+1����
sbit K4=P1^2;//�Ҷ�+2����
sbit K5=P1^1;//�׶�+1����
sbit K6=P1^0;//�׶�+2����
sbit K7=P1^5;//�׶�+3����
sbit K8=P1^6;//�Ҷ�+3����
sbit K9=P1^4;//Ԥ������
sbit beep=P2^0;//�������ӿ�  
sbit RS=P2^7;
sbit E=P2^5;
char miao,fen,num,time,aa;
uchar bb,cc;
uchar code table1[]={"H.T 000:000 R.T "};
uchar code table2[]={"12:00  SEC-1  24"};
//��ʱ�Ӻ���
void delay(uint z)  
{
	uint x;
	uchar y;
	for(x=z;x>0;x--)
  		for(y=110;y>0;y--);
}
//LCD1602Һ��дָ���Ӻ���
void write_com(uchar com)
{
	RS=0;
	P0=com;
	delay(5);
	E=1;
	delay(5);
	E=0;
}
//LCD1602Һ��д�����Ӻ���
void write_date(uchar date)
{
	RS=1;
	P0=date;
	delay(5);
	E=1;
	delay(5);
	E=0;
}
//LCD1602Һ����ʼ���Ӻ���
void LCD1602_init()
{
	uchar i;
	bb=0;    //H.T������ʼ��
	cc=0;    //R.T������ʼ��
	time=0;
	TMOD=0x10;    //��ʱ��1��ʼ��
	TL1=0x00;
	TH1=0x4c;
	EA=1;     //�����ж�
	ET1=1;     //����ʱ��1
	TR1=0;     //��ʱ��1������
	EX0=1;     //���ж�0
	EX1=1;     //���ж�1
	IT0=1;     //�ж�0Ϊ���ش���
	IT1=1;     //�ж�1Ϊ���ش���
	E=0; 
	beep=0;
	miao=0;
	fen=12;
	num=1;
	aa=24;
	write_com(0x38);  //LCD���ó�ʼ��
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);  //LCD��ʾ��ʼ��
	for(i=0;i<16;i++)
	{
	  	write_date(table1[i]);
	}
	write_com(0x80+0x40);
	for(i=0;i<16;i++)
	{
	  	write_date(table2[i]);
	}
}
//���������Ӻ���
void point_lcd(uchar add,uchar dat)
{
	write_com(0x80+add);
	write_date(0x30+dat/100);
	write_date(0x30+(dat%100)/10);
	write_date(0x30+dat%10);
	write_com(0x80+add);
}
//����ɨ���Ӻ���
void keyscan()
{
	if(K3==0)     //K3����H.T������һ
	{
  		while(K3==0);
		bb++;
  		point_lcd(0x04,bb);  //������ʾ����
  		if(K3==0)    //���ּ��
  		{
   			while(K3==0);
   			delay(20);
  		}
	}
	else if(K4==0)    //S4����H.T�����Ӷ�
	{
  		while(K4==0);
		bb=bb+2;
  		point_lcd(0x04,bb);
  		if(K4==0)
  		{
   			while(K4==0);
   			delay(20);
  		}
	}
	else if(K7==0)    //S4����H.T�����Ӷ�
	{
  		while(K7==0);
		bb=bb+3;
  		point_lcd(0x04,bb);
  		if(K7==0)
  		{
   			while(K7==0);
   			delay(20);
  		}
	}
	else if(K5==0)    //S5����R.T������һ
	{
  		while(K5==0);
		cc++;
  		point_lcd(0x08,cc);
  		if(K5==0)
  		{
   			while(K5==0);
   			delay(20);
  		}
	}
	else if(K6==0)    //S6����R.T������2
	{
  		while(K6==0);
		cc=cc+2;
  		point_lcd(0x08,cc);
  		if(K6==0)
  		{
   			while(K6==0);
   			delay(20);
  		}
	}
	else if(K8==0)    //S6����R.T������2
	{
  		while(K8==0);
		cc=cc+3;
  		point_lcd(0x08,cc);
  		if(K8==0)
  		{
   			while(K8==0);
   			delay(20);
  		}
	}
}
//��������ʱ/24s����ʱ
void counter_down()
{
	uchar i;
	if(time>=20)     //ÿ1s����ʱ����һ����
	{
  		miao--;
  		aa--;
  		write_com(0x80+0x4e);  //24s����ʱ��ʾ
  		write_date(0x30+aa/10);
  		write_date(0x30+aa%10);
		write_com(0x80+0x4e);
  		if(aa==0)    //24s��������3s��������
  		{
   			beep=1;
  		 	delay(3000);
   			beep=0;
   			aa=24;
  		}
  		if((miao==0)&&(fen==0))  //���һ�ڱ����Ƿ����
  		{
   			TR1=0;     //��ʱ��1��ͣ
   			write_com(0x80+0x44);
   			write_date(0x30);
   			num++;
   			aa=24;    //24s��ʱ��λ
   			write_com(0x80+0x4e);  //24s����ʱ��ʾ
   			write_date(0x30+aa/10);
   			write_date(0x30+aa%10);
			write_com(0x80+0x4e);
   			if(num<5)    //ÿ�ڽ�������������8s�ļ�ϱ���
   			{
    			for(i=80;i>0;i--)
    			{
     				beep=1;
     				delay(500);
     				beep=0;
     				delay(500);
    			}
   			}
   			if(num==5)    //�ճ�����������������10s������������
   			{
     			beep=1;
     			delay(10000);
     			num=0;
   			}	
   			beep=0;     //�������ر�
			write_com(0x80+0x4b); //����"SEC-?"
			write_date(0x30+num);
			write_com(0x80+0x4b);
			miao=0;     //����ʱ��λ
			fen=12;
  		}
  		if(miao==-1)
  		{
   			miao=59;
   			fen--;
  		}
  		write_com(0x80+0x40);  //���µ���ʱ��ʾ
  		write_date(0x30+fen/10);
  		write_date(0x30+fen%10);
  		write_com(0x80+0x43);
  		write_date(0x30+miao/10);
  		write_date(0x30+miao%10);
		write_com(0x80+0x43);
  		time=0;
	}
}
//������
void main()
{
	LCD1602_init();
	while(1)
	{
  		keyscan();  //�����������
	}
}
//�ⲿ0�ж��Ӻ���
void wb0() interrupt 0  //����ʱ�俪ʼ/��ͣ
{
	TR1=~TR1;     //��ʱ��1����/��ͣ
	if(TR1==1)  //������ʱ����ʱ��S1���¶�ʱ������ֹͣ����
	{
  		PT1=0;
	}
	else   //����ʱ������ʱ��S1���µ���ʱ��������
	{
  		PT1=1;
	}
	if(K1==0)     //���ּ��
	{
  		while(K1==0);
   		counter_down();
  	//	delay(20);
	}
}
//�ⲿ1�ж��Ӻ���
void wb1() interrupt 2   //24s����ʱ���¿�ʼ
{
	aa=24;
	write_com(0x80+0x4e);   //24s����ʱ��ʾ
	write_date(0x30+aa/10);
	write_date(0x30+aa%10);
	write_com(0x80+0x4e);
	if(K2==0)      //���ּ��
	{
  		while(K2==0)
  		{
   			counter_down();
  		}
  		delay(20);
	}
}
//��ʱ��1�ж��Ӻ���
void t1() interrupt 3   //��ʱ��1�ж�20��Ϊ1s
{
	time++;
	TL1=0x00;
	TH1=0x4c;
	counter_down();     //����ʱ 
}



