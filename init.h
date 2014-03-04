//==============================================//
//	    		Include Header Files			//
//==============================================//
#include <pic.h>

//==============================================//
//	    		union define				    //
//==============================================//
#ifndef __DEFINE_DATA
#define __DEFINE_DATA

union ulword {
	unsigned long int lword;
	unsigned char byte[4];
};

union uword {
	unsigned int word;		
	unsigned char byte[2];
	struct{
		unsigned char B0 :1;
		unsigned char B1 :1;
		unsigned char B2 :1;
		unsigned char B3 :1;
		unsigned char B4 :1;
		unsigned char B5 :1;
		unsigned char B6 :1;
		unsigned char B7 :1;
		unsigned char B8 :1;
		unsigned char B9 :1;
		unsigned char B10:1;
		unsigned char B11:1;
		unsigned char B12:1;
		unsigned char B13:1;
		unsigned char B14:1;
		unsigned char B15:1;
	}bits;
};

union ubyte {
	unsigned char byte;
	struct{
		unsigned char B0 :1;
		unsigned char B1 :1;
		unsigned char B2 :1;
		unsigned char B3 :1;
		unsigned char B4 :1;
		unsigned char B5 :1;
		unsigned char B6 :1;
		unsigned char B7 :1;
	}bits;
};

#endif
//==============================================//
//	    EEPROM ADDRESS							//
//==============================================//
//#define EA_bSoftLv		0x00
//#define EA_bFamilyLv		0x01
//#define EA_bLadyLv		0x02


//==============================================//
//	    Define I/O								//
//==============================================//

//==============================================//
//	       DEFINE DATA							//
//==============================================//



//==============================================//
//	       GLOBAL DATA							//
//==============================================//


//==============================================//
//	    	­ì«¬«Å§i							//
//==============================================//
extern void Init_System(void);





