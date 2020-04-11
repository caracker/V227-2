#include	"led.h"
#include "../../head_extern.h"
#include	"../key/key.h"
#include	"../motor/motor.h"

void led_init(void)
{ 
	$ led1 out,high;
	led1=led_off;
	$ led2 out,high;
	led2=led_off;

}
/*led_mode
*led_mode
		0:ÂÌµÆÁÁ3ÃëºóÏ¨Ãğ
		1:LED1µÆ¿ìÉÁ£¨ÁÁ0.2£¬Ãğ0.2S£©
		2:
*/
void led_even(void)
{
	if(f_charging_full)
	{
		led1=led_on;
	}
	else
	{
		if(led_time<50)	led1=led_on;
		else if(led_time<100)	led1=led_off;
		else					led_time=0;

	}
}


