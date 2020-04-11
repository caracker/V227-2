#ifndef __head_extern_H
#define __head_extern_H	

extern BYTE	Sys_Flag;
extern BIT		f_work		:	Sys_Flag.0;		//开关机
extern BIT		f_charging	:	Sys_Flag.1;		//充电
extern bit    	f_key_scan	:	Sys_Flag.3;		//按键扫描
extern bit      f_charging_full:Sys_Flag.4;		//充满
extern BIT		f_low		:	Sys_Flag.5;		//开关机
extern byte motor_state,motor_state_save;		//马达工作模式0~7
extern bit     f_stop;
extern byte count;//T16计数
extern byte S1_count,s2_count;//按键计数
extern word motor_time;
extern word pwm_num;
extern WORD sleep_time,work_time;
extern bit pwm_bit;
extern byte rate;
extern byte pwm_duty,pwm_cnt;
extern byte pwm_speed;   
extern byte pwm_hz;
extern byte pwm_time;
extern word pwm20_40_time;
extern byte motor_state_save;
extern word time_10sec;
extern bit led_times;
extern byte check_time,low_count,led_time;
extern byte s1_lastime;
extern byte led_time2;
extern byte led_cnt;
extern byte hot_mode;
extern bit f_heating;
extern word hot_time;
extern byte led_time3;
extern bit f_low33;
extern word hot_time2;
extern byte hot_mode;
extern byte ad_time;
extern word ad_val;
extern byte beep_times;


extern word cur_ad;
extern word hot_ad;
extern word water_ad;
extern byte water_mode;
extern byte water_modesave;
extern byte led1_time;
extern byte sec3;
extern byte led_mode;
extern word min5;
#endif