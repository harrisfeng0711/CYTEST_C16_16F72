//===============================================//
// 程式編號: CYTEST-C16
// 程式名稱: 乘除法組合語言驗證程式
// 程式撰寫: Hj
// 晶片型號: PIC16F72
// 開始時間: 
// 完成時間: 
// 程式版本: 
//-----------------------------------------------//
// 版本編號 : 
// 發行日期 : 
// 摘要記事 : 
//===============================================//


 
//==============================================//
//	    		Include Header Files			//
//==============================================//
#include "init.h"


//==============================================//
//	    	Configuartion Bit Setting			//
// osc config.     : XT/HS/RC/LP				//
// watchdog        : WDTEN/WDTDIS				//
// power up timer  : PWRTEN/PWRTDIS				//
// brown out reset : BOREN/BORDIS				//
// code protection : PROTECT/UNPROTECT			//
//==============================================//
__CONFIG (XT & WDTDIS & PWRTEN & BOREN & PROTECT);

//==============================================//
//				函式原型宣告					//
//==============================================//


//==============================================//
//				參數定義						//
//==============================================//


//==============================================//
//				暫存器定義						//
//==============================================//
static unsigned char r0,r1,r2,r3,r4,r5,r6;
static unsigned int cnt0,cnt1;
static unsigned int TEMP;
static union uword temp;

static unsigned int DRESULT;
static unsigned char DREMAIN;

static union ulword dresult,dcnt0;
static unsigned int dcnt1;
static unsigned char dremain;


const unsigned char aa[]={1,2};
const unsigned char bb[]={9,10,11,12};
const unsigned char cc[] = {7,7,7};
const struct scan
{
	const unsigned char *f[3];
}table[1]={{aa,bb,cc}};


const unsigned char *cp;


unsigned int arrAD[8] = {512,120,358,887,978,216,772,512};
unsigned int adv=0;

unsigned int filter(unsigned int *ptArr);
//==============================================//
//	   				中斷副程式 					//
//==============================================//
static void interrupt isr (void)
{


}


//==============================================//
//	    	 	MAIN PROGRAM 					//
//==============================================//
void main (void)
{
	Init_System ();
	GIE = 1;

	if (CARRY == 1)
		r0 = 1;
		
//	cp = &table[0];
//	cp = table[0].f[0];
//	r0 = *cp;
	
	
	
	adv = filter(arrAD);
	
	
	
	
	
	while (1)
	{
		
//----------------------------------------------------------------------
// 驗證 mul8x8 組語
		for (cnt0=0;cnt0<256;cnt0++)
		{
			//cnt1 = 0;
			
			for (cnt1=0;cnt1<256;cnt1++)
			{
				TEMP = cnt0*cnt1;
				r0 = cnt0;
				r1 = cnt1;
				
				#asm
				pMul8x8:	// r1 * r0 = r3 : r2
				        CLRF    _r2			//; 1 uS * 1 = 1 uS
				        CLRF    _r3			//; 1 uS * 1 = 1 uS
			
				        MOVLW   0x8			//; 1 uS * 1 = 1 uS
				        MOVWF   _r4			//; 1 uS * 1 = 1 uS
				        
				        MOVF    _r0,W		//; 1 uS * 1 = 1 uS
				        //CLRC				        
				        //BCF		0x3,0
				ML10:
				        RRF     _r1,F		//; 1 uS * 8 = 8 uS
				//      SKPNC				//; 1 uS * 8 = 8 uS
						BTFSC 	0x3,0
				        ADDWF   _r3,F		//; 1 uS * 8 = 8 uS

				        RRF     _r3,F		//; 1 uS * 8 = 8 uS
				        RRF     _r2,F		//; 1 uS * 8 = 8 uS

				        DECFSZ  _r4,F		//; 1 uS * 8 = 8 uS
				        goto    ML10		//; 2 uS * 8 = 16 uS
				//      RETURN				//; 2 uS * 1 = 2 uS			
				#endasm
				temp.byte[1] = r3;
				temp.byte[0] = r2;
				
				if (TEMP != temp.word)
					while(1);
			}
		}
//----------------------------------------------------------------------
// 驗證 div16x8
		for (dcnt0.lword=0;dcnt0.lword<65536;dcnt0.lword++)
		{
			dcnt1 = 1;

			for (dcnt1=1;dcnt1 <256 ;dcnt1++)
			{
				DRESULT =(unsigned int) (dcnt0.lword/dcnt1);
				DREMAIN =(unsigned char) (dcnt0.lword%dcnt1);

				r1 = dcnt0.byte[1];
				r0 = dcnt0.byte[0];
				r2 = (unsigned char)dcnt1;
				
				#asm
						CALL	pDiv16x8
						goto	JMPOUT
				
				
				pDiv16x8:	// r1,r0 / r2 = r1,r0..r3
				        CLRF    _r3			//; 1 uS * 1 = 1 uS
				        CLRF    _r4			//; 1 uS * 1 = 1 uS
				
				        CALL    DV10		//; 2 uS * 1 = 2 uS
				DV10:
				        MOVLW   8			//; 1 uS * 2 = 2 uS
				        MOVWF   _r5			//; 1 uS * 2 = 2 uS
				DV20:
				        //CLRC				//; 1 uS * 8 * 2 = 16 uS
				        BCF		0x3,0
				        RLF     _r1,F		//; 1 uS * 8 * 2 = 16 uS
				        RLF     _r3,F		//; 1 uS * 8 * 2 = 16 uS
				        RLF     _r4,F		//; 1 uS * 8 * 2 = 16 uS
				;---------------------------------------; r4,r3 - r2 = r4,r3
				        INCF    _r1,F		//; 1 uS * 8 * 2 = 16 uS
				
				        MOVF    _r2,W		//; 1 uS * 8 * 2 = 16 uS
				        SUBWF   _r3,F		//; 1 uS * 8 * 2 = 16 uS
				        //SKPNC				//; 2 uS * 8 * 2 = 32 uS
				        BTFSC	0x3,0
				        goto    DV30
				
				        MOVLW   1			//; 1 uS * 8 * 2 = 16 uS
				        SUBWF   _r4,F		//; 1 uS * 8 * 2 = 16 uS
				        //SKPNC				//; 2 uS * 8 * 2 = 32 uS
				        BTFSC	0x3,0
				        goto    DV30
				;---------------------------------------; r4,r3 + r2 = r4,r3
				        DECF    _r1,F		//; 1 uS * 8 * 2 = 16 uS
				
				        MOVF    _r2,W		//; 1 uS * 8 * 2 = 16 uS
				        ADDWF   _r3,F		//; 1 uS * 8 * 2 = 16 uS
				        //SKPNC				//; 1 uS * 8 * 2 = 16 uS
				        BTFSC	0x3,0
				        INCF    _r4,F		//; 1 uS * 8 * 2 = 16 uS
				DV30:
				        DECFSZ  _r5,F		//; 1 uS * 8 * 2 = 16 uS
				        goto    DV20		//; 2 uS * 8 * 2 = 32 uS
				;---------------------------------------
				        MOVF    _r1,W		//; 1 uS * 2 = 2 uS
				        MOVWF   _r6			//; 1 uS * 2 = 2 uS
				
				        MOVF    _r0,W		//; 1 uS * 2 = 2 uS
				        MOVWF   _r1			//; 1 uS * 2 = 2 uS
				
				        MOVF    _r6,W		//; 1 uS * 2 = 2 uS
				        MOVWF   _r0			//; 1 uS * 2 = 2 uS
				        RETURN				//; 2 uS * 2 = 4 uS	
				
				JMPOUT:
				#endasm
				
				dresult.byte[1] = r1;
				dresult.byte[0] = r0;
				dremain = r3;
				
				if ((DRESULT != dresult.lword)||(DREMAIN != dremain))
					while(1);
			}
		}
		while (1);		
		
	}
	


}

//==============================================
// 電壓濾波
//==============================================
unsigned int filter(unsigned int *ptArr)
{
    unsigned char i,j;
    unsigned int value_buf[8];
    unsigned int sum,tmp;

	// 採樣N個資料
	for (i=0;i<8;i++)
		value_buf[i]=*ptArr++;
	
	// 把N次採樣值按小到大排列, 排序採用冒泡法        
    for (i=0;i<7;i++)
    {
        for (j=(i+1);j<8;j++)
        {
            if (value_buf[i] > value_buf[j])
            {
                tmp = value_buf[i];               
                value_buf[i] = value_buf[j];
                value_buf[j] = tmp;
            }
        }
    }

	sum=0;
	sum+=value_buf[2];
	sum+=value_buf[3];
	sum+=value_buf[4];
	sum+=value_buf[5];
	sum>>=2;

    return sum;
}
