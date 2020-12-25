

#include "reg52.h" //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include "lcd.h"
#include "i2c.h"
#define LCD1602_DATAPINS P0

#define GPIO_KEY P1

unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ
unsigned char KeyState;
//������Ű���״̬
unsigned char dat[] = "123a456b789c*0#d";

void DelayMs(unsigned int x);
void Delay10ms(); //��ʱ50us
void KeyDown();		//��ⰴ������
char s[6] = "INPUT:";
char c[5] = "READ:";
int i, j;
char shu[10] = "          ";
char chu[11] = "           ";
int p = 0;
void main(void)
{
	unsigned char i;
	LcdInit();
	KeyState = 0;

	j = 0;
	while (1)
	{
		KeyDown();
	}
}

void KeyDown(void)
{
	char a;
	GPIO_KEY = 0x0f;
	if (GPIO_KEY != 0x0f)
	{
		Delay10ms();
		if (GPIO_KEY != 0x0f)
		{
			KeyState = 0;
			//������
			GPIO_KEY = 0X0F;
			// 			Delay10ms();
			switch (GPIO_KEY)
			{
			case (0X07):
				KeyValue = 0;
				break;
			case (0X0b):
				KeyValue = 1;
				break;
			case (0X0d):
				KeyValue = 2;
				break;
			case (0X0e):
				KeyValue = 3;
				break;
				//				default:	KeyValue=17;	//������ظ�17��˼�ǰ������ȫ�����
			}
			//������
			GPIO_KEY = 0XF0;
			Delay10ms();
			switch (GPIO_KEY)
			{
			case (0X70):
				KeyValue = KeyValue;
				break;
			case (0Xb0):
				KeyValue = KeyValue + 4;
				break;
			case (0Xd0):
				KeyValue = KeyValue + 8;
				break;
			case (0Xe0):
				KeyValue = KeyValue + 12;
				break;
				//				default:	KeyValue=17;
			}
			if (dat[KeyValue] == 'a')
			{
				LcdWriteCom(0x80);
				for (i = 0; i < 6; i++)
					LcdWriteData(s[i]);
			}
			else if (dat[KeyValue] == 'b')
			{
				LcdWriteCom(0x80);
				for (i = 0; i < 16; i++)
					LcdWriteData(' ');
				LcdWriteCom(0x80);
				for (i = 0; i < 6; i++)
					LcdWriteData(s[i]);
				shu[10] = "          ";
				j = 0;
			}
			else if (dat[KeyValue] == 'c')
			{
				for (i = 0; i <= j; i++)
					At24c02Write(1 + i, shu[i]);
			}
			else if (dat[KeyValue] == 'd')
			{
				for (i = 0; i <= j; i++)
					chu[i] = At24c02Read(1 + i);

				LcdWriteCom(0x80 + 0x40);
				for (i = 0; i < 5; i++)
					LcdWriteData(c[i]);
				for (i = 0; i < 10; i++)
					LcdWriteData(shu[i]);
			}
			else
			{
				shu[j] = dat[KeyValue];
				LcdWriteData(shu[j]);
				j++;
			}
			p++;
			while ((a < 50) && (GPIO_KEY != 0xf0)) //��ⰴ�����ּ��
			{
				Delay10ms();
				a++;
			}
			a = 0;
		}
	}
}

void Delay10ms(void) //��� 0us
{
	unsigned char a, b, c;
	for (c = 1; c > 0; c--)
		for (b = 38; b > 0; b--)
			for (a = 130; a > 0; a--)
				;
}
void DelayMs(unsigned int x) //0.14ms��� 0us
{
	unsigned char i;
	while (x--)
	{
		for (i = 0; i < 13; i++)
		{
		}
	}
}
