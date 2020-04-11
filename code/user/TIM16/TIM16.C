#include	"TIM16.h"

void T16_init(void)
{
	$  T16M     IHRC, /1, BIT11;    // T16 递增时间 = 16MHz。
                                        // 触发时间 = 2^12 * 1uS /16 = 256 uS
	$ INTEN t16;	//中断源
	INTRQ = 0; 		// 清除INTRQ
	DISGINT	 		// 禁用全局中断
	ENGINT 			// 启用全局中断
}


