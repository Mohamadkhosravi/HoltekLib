
#include "RCC.h"

void RCC_Init()
{
	_scc = 0b00000000;
	#if CONFIG_CLOCK_OVER == INTERNAL_8_MHZ
		_hircc=0b00001001;
	#elif CONFIG_CLOCK_OVER == INTERNAL_4_MHZ
		_hircc=0b00000101;
	#else
		_hircc=0b00000001;
	#endif
	
	_wdtc =0b10101111;

}



