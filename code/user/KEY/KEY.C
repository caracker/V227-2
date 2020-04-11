#include	"KEY.h"
#include "../../head_extern.h"
#include	"../motor/motor.h"
#include	"../comparator/comparator.h"
#include	"../led/led.h"
#include	"../hot/hot.h"
extern byte motor_state_temp;
extern byte hot_mode_temp;
byte char_cnt;
void key_init(void)
{
	$ s1 IN,pull;
	 char_cnt=0;
}

void check_charging(void)
{
	if(hot_Ad<10)
	{
		char_cnt++;
		if(char_cnt>100)
		{
			char_cnt=100;
			f_charging_full=1;
		}
	}
	else
	{

	}
}
void key_scan(void)
{
	if(f_key_scan )
	{
		f_key_scan=0;
		s1_even();	
		check_charging();
	}
}

void s1_even(void)
{
	if(s1==0)
	{
		if(S1_count<250)	S1_count++;
		if(S1_count>10) //³¤°´
		{
			if(work_time<60000)work_time++;
			if(work_time<5*60*100)
			{
				led2=led_on;
			}
			else
			{
				led2=led_off;
			}
				
		}
	}
	else
	{	
		if(S1_count>3 && S1_count<150)
		{
		
		}
		S1_count=0;
		led2=led_off;
		work_time=0;
	}
}

