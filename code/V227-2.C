#include	"extern.h"
#include	"./user/TIM16/TIM16.h"
#include	"./user/key/key.h"
#include	"./user/led/led.h"
#include	"./user/hot/hot.h"
#include	"./user/motor/motor.h"
#include	"./user/comparator/comparator.h"
#include	"./user/STOPSYS/STOPSYS.h"
#include	"./user/adc/adc.h"
#include 	"head.h"
//.Writer     Limit   $ + 5
extern byte motor_state_temp;
extern byte hot_mode_temp;
byte  sec_cnt;
extern byte char_cnt;
void data_init(void)
{
	f_work=0;	
	f_key_scan=0; 
	f_charging_full=0;
	count= 39;  
	work_time=0;
}
void	FPPA0 (void)
{

	.ADJUST_IC	SYSCLK=IHRC/2, IHRC=16MHz, VDD=5V;
	T16_init();
	key_init();
	led_init();
	adc_init();
	data_init();

	while (1)
	{
		key_scan();
		adc_even();
		led_even();
 	}
}
byte count2;
void	Interrupt (void)
{
	pushaf;

	if (Intrq.T16)
	{	
		Intrq.T16	=	0;
		if (--count == 0)					
		{
			count= 39;          // 256 uS * 39 = 9,984 uS ¨P 10 mS
	 		f_key_scan=1;
			if(led_time<250)led_time++;
			if (--count2 == 0)
			{
				count2=100;
			}
		}
	}

	popaf;
}

