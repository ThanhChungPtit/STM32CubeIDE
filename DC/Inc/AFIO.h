#ifndef __AFIO_H
#define __AFIO_H

#include <stdint.h>

typedef struct {
	uint32_t EVCR ;
	uint32_t MAPR ;
	uint32_t EXTICR1 ;
	uint32_t EXTICR2 ;
	uint32_t EXTICR3 ;
	uint32_t EXTICR4 ;
} AFIO_TypeDef ;

#define AFIO_BASE ((volatile AFIO_TypeDef*) 0x40010000UL)



#endif
