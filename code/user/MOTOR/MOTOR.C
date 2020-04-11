
#include	"motor.h"
#include "../../head_extern.h"
#include	"../key/key.h"
/*	输出频率 = Y ÷ [256 × S1 × (S2+1) ]
*	输出空占比 = ( K＋1 ) ÷ 256×100%
*	Y = tm2c[7:4] : Timer2 所选择的时钟源频率
*	K = tm2b[7:0] : 上限寄存器设定的值(十进制)
*	S1 = tm2s[6:5] : 预分频器设定值 (1, 4, 16, 64)
*	S2 = tm2s[4:0] : 分频器值 (十进制，1 ~ 31)
*/

void beep_init(void)
{
	$ beep_pin out,low;
}
void motor_init(void)
{ 
	tm2ct=0;
	tm2b = 255;			 //上限寄存器    k=127
	tm2c = 0b_0001_00_1_0;	 // 系统时钟, 输出 = PA4, PWM 模式
	tm2s = 0b_0011_0011;	 // 8位pwm:256, 预分频 = 1, 分频 = 2   S1=1  S2=1

	motor_off;
}
byte motor_state_temp;
void motor_50pwm(void)
{ 
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 127;	
		motor_on;
	}
}
void motor_75pwm(void)
{	
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 191;	
		motor_on;
	}
}
void motor_100pwm(void)
{
	
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 255;	
		motor_on;
	}
}
void motor_20_40pwm(void)
{	
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_1111_1111;//15hz  2-99% 3.5s
		tm2b = 1;
		pwm_num=1;
		motor_on;
	}
	if(motor_time>5)
	{
		motor_time=0;
		if(pwm_num<62)
		{
			pwm_num++;
		}
		else
		{
			pwm_num=1;
		}
		tm2b = pwm_num;	
		motor_on;
	}
	
}
void motor_400ms(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 255;	
		motor_on;
	}
	if(motor_time<40)
	{
		motor_on;
	}
	else if(motor_time<80)
	{
		motor_off;
	}
	else
	{
		motor_time=0;	
	}
}
void motor_200ms(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 255;	
		motor_on;
	}
	if(motor_time<20)
	{
		motor_on;
	}
	else if(motor_time<40)
	{
		motor_off;
	}
	else
	{
		motor_time=0;	
	}
}
void motor_1000ms(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 255;	
		motor_on;
	}
	if(motor_time<20)
	{
		motor_on;	
	}
	else if(motor_time<40)
	{
		motor_off;	
	}
	else if(motor_time<60)
	{
		motor_on;	
	}
	else	if(motor_time<80)
	{
		motor_off;	
	}
	else if(motor_time<100)
	{
		motor_on;	
	}
	else if(motor_time<120)
	{
		motor_off;	
	}
	else if(motor_time<220)
	{
		motor_on;	
	}
	else if(motor_time<245)
	{
		motor_off;
	}
	else
	{
		motor_time=0;	
	}
}

void mode1_even(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 51;	
		motor_on;
		motor_time=0;
	}
	if(motor_time<10*60)
	{
		motor_on;
	}
	else
	{
	
		motor_off;
		f_work=0;
	}
}
void mode2_even(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 76;	
		motor_on;
		motor_time=0;
	}
	if(motor_time<10*60)
	{
		motor_on;
	}
	else
	{
	
		motor_off;
		f_work=0;
	}
}
void mode3_even(void)
{
	if(motor_state != motor_state_temp)
	{
		motor_state_temp=motor_state;
		tm2s = 0b_0011_0011;//100hz
		tm2b = 127;	
		motor_on;
		motor_time=0;
	}
	if(motor_time<10*60)
	{
		motor_on;
	}
	else
	{
	
		motor_off;
		f_work=0;
	}
}
void motor_even(void)
{
	if(f_work)
	{
		if(water_modesave>=2)
		{
			switch(motor_state)
			{
				case 0:
					motor_off;
					break;
				case 1:
					mode1_even();
					break;
				case 2:
					mode2_even();
					break;
				case 3:
					mode3_even();
					break;
				default :
					motor_state=0;
					break;
			}
			if(motor_state>=2)
			{
				if(hot_ad<2064)//大于50度
				{
					motor_state=1;
					beep_times=1;
				}
			}
		}
		else
		{
			motor_off;
		}
		if(	water_modesave!=water_mode)
		{
			if(	water_modesave>=2 && water_mode<=1)//水量用完
			{
				//水量不足
				beep_times=3;
				led_mode=1;
			}
			if(water_modesave<=1 && water_mode>=2)
			{
				//水量达到低水位
				led_mode=0;   
			}
			if(water_modesave<=2 && water_mode==3)
			{
				//水量达到高水位
				beep_times=3;
				led_mode=0;   
			}
			water_modesave=water_mode;
		}
		if(water_modesave<=1)
		{
			if(min5>60*5) //，5分钟内不加水自动关机。
			{
				f_work=0;	
			}
		}
		else
		{
			min5=0;
		}
	}
	else
	{
		motor_off;	
	}

}

word been_cnt;
void beep_even(void)
{
	if(beep_times)
	{
		been_cnt++;
		if(been_cnt<780)
		{
			if(beep_pin)beep_pin=0;
			else        beep_pin=1;
		}
		else  if(been_cnt<780*2)
		{
			beep_pin=0;
		}
		else
		{
			been_cnt=0;
			beep_times--;
		}
	}
	else
	{
		been_cnt=0;
		beep_pin=0;
	}
}