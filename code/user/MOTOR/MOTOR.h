void motor_init(void);
void motor_even(void);
void pwm_init(void);
#define motor_on	tm2c = 0b_0001_10_1_0;
#define motor_off	tm2c = 0b_0001_00_1_0;

beep_pin equ pa.7

void beep_init(void);
void beep_even(void);