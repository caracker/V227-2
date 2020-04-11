#include	"ADC.h"
#include "../../head_extern.h"
#include	"../motor/motor.h"
static	void	Shifter_K (void);
static	void	Get_AD_By_K (void);
extern DWORD	div_src4;
extern WORD	div_val2, div_res2;
void	DWord_Div_Word (void);
extern byte pwm_nummax;
//ADC
void ADC_init(void)
{
	//io
	$ Pa.4 IN,nopull;//PB0没上拉输入

	$ ADCC Enable, Pa4; // 设定PB0 当ADC 输入
	$ ADCM 12BIT, /16; // 建议 /16 @系统时钟=8MHz
	ADCRGC=0b_101_0_00_00; //1.2v
}
/***************************************************************************/
/*
/*						滑动滤波器
/*
/*						
/*
/*
******************************************************************************/
#define	K	3	//	1 ~ 4
static	WORD	AD_Shift, AD_Filter;
static	void	Shifter_K (void)
{
	AD_Shift	=	AD_Filter;
	A			=	K;
	do
	{
		AD_Shift >>= 1;
	} while (--A);
}
#define	K2	3	//	1 ~ 4
static	WORD	AD_Shift2, AD_Filter2;
static	void	Shifter_K2 (void)
{
	AD_Shift2	=	AD_Filter2;
	A			=	K2;
	do
	{
		AD_Shift2 >>= 1;
	} while (--A);
}
WORD	AD_Val2;
/*	Ruler	:	AD_Val  =  (ADCR + (2^k-1)*older ADCR) / 2^k;
	K = 1	:	AD_Val  =  (ADCR + older ADCR) / 2;
	K = 2	:	AD_Val  =  (ADCR + 3 * older ADCR) / 4;
	K = 3	:	AD_Val  =  (ADCR + 7 * older ADCR) / 8;

	AD_Filter	= (2^k)*Older ADCR,		AD_Shift = Older ADCR.
*/
static	void	Get_AD_By_K2 (void)
{
	AD_Val2		=	(ADCRH << 8) | ADCRL;	//	Get 12 Bit of ADC
	AD_Val2		>>=	4;						//

	Shifter_K2 ();
	AD_Filter2	-=	AD_Shift2;				//	Low Pass Filter
	AD_Filter2	+=	AD_Val2;					//

	Shifter_K2 ();
	AD_Val2		=	AD_Shift2;				//	Get new 12 Bit of ADC
}

//static	WORD	AD_Val;
/*	Ruler	:	AD_Val  =  (ADCR + (2^k-1)*older ADCR) / 2^k;
	K = 1	:	AD_Val  =  (ADCR + older ADCR) / 2;
	K = 2	:	AD_Val  =  (ADCR + 3 * older ADCR) / 4;
	K = 3	:	AD_Val  =  (ADCR + 7 * older ADCR) / 8;

	AD_Filter	= (2^k)*Older ADCR,		AD_Shift = Older ADCR.
*/
static	void	Get_AD_By_K (void)
{
	AD_Val		=	(ADCRH << 8) | ADCRL;	//	Get 12 Bit of ADC
	AD_Val		>>=	4;						//

	Shifter_K ();
	AD_Filter	-=	AD_Shift;				//	Low Pass Filter
	AD_Filter	+=	AD_Val;					//

	Shifter_K ();
	AD_Val		=	AD_Shift;				//	Get new 12 Bit of ADC
}

void	ADC_Module (void)
{	//	There are three ways to read AD value
	WORD	buf [3];

	#if defined(ADCDI)
		ADCDI	=	0x0F;	//	PB0 ~ PB3 is for AD
	#elif defined(PBDIDR)
		PBDIDR	=	0x0F;	//	PB0 ~ PB3 is for AD
	#else
		$ PBDIER	0xF0;	//	PB0 ~ PB3 is for AD
	#endif
	$ ADCM	/4, 12BIT;

	AD_Filter	=	0;		//	You can initial the value from ADCR << K.
							//	use 0 is easy, but not good.
	while (1)
	{


		// 5	:	Use shift K, to get new ADC value
		$ ADCC	Enable, PB4;
		AD_Start	=	1;
		.Wait1		AD_Done;

		Get_AD_By_K ();
	}
}


DWORD	mul_t4;
WORD	mul_x2;
WORD	mul_y2;
void	Word_Mul_Word (void)
{	//	mul_t4[D]	=	mul_x2[W] * mul_y2[W]
	mul_t4$3	=	0;
	mul_t4$2	=	0;

	BYTE	cnt;
	cnt	=	16;

	do
	{
		mul_x2	>>=	1;
		if (CF)
		{
			mul_t4	+=	(mul_y2 << 16);
		}
		mul_t4	>>>=	1;
	} while (--cnt);
}


DWORD	div_src4;
WORD	div_val2, div_res2;
void	DWord_Div_Word (void)
{	//	div_src4[D] / div_val2[W]	=	div_src4[D] * div_val2[W] + div_res2[W]
	BYTE	div_cnt, div_tmp;
	div_cnt		=	0;
	div_res2	=	0;

	do
	{
		div_src4	<<=		1;
		div_res2	<<<=	1;
		div_tmp		<<<=	1;
		div_cnt++;
		A	=	(div_res2 - div_val2) >> 8;

		if (div_tmp.0 || ! CF)
		{
			div_res2$1	=	A;
			div_res2$0	-=	div_val2$0;
			div_src4.0	=	1;
		}
	} while (! div_cnt.5);
}


WORD Data;
void GET_ADC(void)
{
	AD_START = 1;				 // 开始ADC 转换
	do
	{
		Nop;
	}while (!AD_DONE) ; 		// 等待ADC 转换结果				// 2 字节结果: ADCRH 和ADCRL
//	Data = (ADCRH << 4) | (ADCRL & 0xf0) >> 4;  //12位的AD 转换的结果
	
	Get_AD_By_K();
//	.PRINTF	("data = %d mV",data);

}

void adc_even(void)
{


	AD_START = 1;				 // 开始ADC 转换
	do
	{
		Nop;
	}while (!AD_DONE) ; 		// 等待ADC 转换结果				// 2 字节结果: ADCRH 和ADCRL
	hot_Ad = (ADCRH << 4) | (ADCRL & 0xf0) >> 4;  //12位的AD 转换的结果
}
