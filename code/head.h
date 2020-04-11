#ifndef __HEAD_H
#define __HEAD_H	

//*************************************************//
//变量的定义，修改变量必须同步修改head_extern.h
//***********************************************//

BYTE	Sys_Flag;
BIT		f_work		:	Sys_Flag.0;		//开关机
BIT		f_charging	:	Sys_Flag.1;		//充电
bit     f_key_scan	:	Sys_Flag.3;		//按键扫描
bit     f_charging_full:Sys_Flag.4;		//充满
BIT		f_low		:	Sys_Flag.5;		//开关机
bit     f_stop;
byte motor_state,motor_state_save;		//马达工作模式0~7
byte count;//T16计数
byte S1_count,S2_count;//按键计数
word motor_time;
WORD sleep_time,work_time; 
word pwm_num;
byte low_count,led_time;
byte s1_lastime;
byte led_time2;
byte led_cnt;
bit f_heating;
word hot_time;
byte led_time3;
bit f_low33;
word hot_time2;
byte hot_mode;
byte ad_time;
word ad_val;

byte beep_times;
word cur_ad;
word hot_ad;
word water_ad;
byte water_mode;
byte water_modesave;
byte led1_time;
byte sec3;
byte led_mode;
word min5;
#endif