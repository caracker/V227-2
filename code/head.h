#ifndef __HEAD_H
#define __HEAD_H	

//*************************************************//
//�����Ķ��壬�޸ı�������ͬ���޸�head_extern.h
//***********************************************//

BYTE	Sys_Flag;
BIT		f_work		:	Sys_Flag.0;		//���ػ�
BIT		f_charging	:	Sys_Flag.1;		//���
bit     f_key_scan	:	Sys_Flag.3;		//����ɨ��
bit     f_charging_full:Sys_Flag.4;		//����
BIT		f_low		:	Sys_Flag.5;		//���ػ�
bit     f_stop;
byte motor_state,motor_state_save;		//��﹤��ģʽ0~7
byte count;//T16����
byte S1_count,S2_count;//��������
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