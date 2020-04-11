#include	"comparator.h"
#include "../../head_extern.h"
#include	"../key/key.h"
#include	"../led/led.h"
#include	"../motor/motor.h"
#include	"../hot/hot.h"
void comparator_test(void);
void comparator_init(void)
{
//	(gpcs.5=0 & gpcs.4=0)		V internal R = (9+n)/32*VDD, n = gpcs[3:0] in decimal
//	(gpcs.5=1 & gpcs.4=1)		V internal R = (n+1)/32*VDD, n = gpcs[3:0] in decimal					
//	(gpcs.5=0 & gpcs.4=1)		V internal R = (n+1)/24* VDD, n = gpcs[3:0] in decimal
//	(gpcs.5=1 & gpcs.4=0)		V internal R = (9+n)/40*VDD, n = gpcs[3:0] in decimal

// gpcs = 0x20 | 8;					// choose case 3 and R=8 => 2.8V
//	gpcc = 0b1_0_00_010_0;			 // 启用比较器, 负输入=band-gap, 正输入=Vinternal R
//	$ gpcs = 0b1_0_10_1000;
		/*	At bit 5 ~ 0, you can use the follow items
				VDD*(9~24)/32
				VDD*(1~16)/24
				VDD*(9~24)/40
				VDD*(1~16)/32

                        Ex :    $ GPCS  Output, VDD*15/32
                                $ GPCS  Output, VDD/2
		*/
//	$ gpcs   VDD*10/32;;    	//3.73v
//	$ gpcs  VDD*7/24;    		//3.96v
//	$ gpcs   VDD*11/32;;    	//3.4v
	$ gpcs   VDD*13/32;;    	//3.12v
//	$ gpcs  VDD*8/24;    		//3.51v
//	$ gpcs   VDD*12/40;;    	//3.86v								
//	$ gpcs   VDD*9/32;;    		//4.13v
//	$ gpcs   VDD*11/40;;    	//4.22v
	$ gpcc  Enable, BANDGAP,P_R;  // 启用比较器, 负输入=band-gap, 正输入=Vinternal R
	$ gpcs   VDD*14/40;; 
//	while(1)
	{
//		comparator_test();
	}
	
}

void comparator_test(void)
{

	if(gpcc.6 )  //VDD大于3.3v
	{
		nop;
	}
	else	//VDD小于3.3v
	{
		nop;
	}

}
// gpcs  VDD*14/40; 
//  $ gpcs   VDD*13/32;    	//3.12v
//4.低电保护，当电池电压低于3V时，LED1-4闪三下（亮200mS，灭200mS）后产品关机，需要充电激活才能开机。
void check_power_even(void)
{
	if(f_work )
	{
		$ gpcs   VDD*13/32;;
		if(gpcc.6 )  //VDD大于3v
		{
			low_count=0;
		}
		else	//VDD小于3v
		{
			low_count++;
			if(low_count>10)
			{
				low_count=0;
				f_low=1;
				f_work=0;
				motor_state=0;
				f_heating=0;

			}				
		}
	}
	else
	{
		low_count=0;
	}

}
