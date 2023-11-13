/*
 * main.h
 *
 *  Created on: 17 Aug 2022
 *      Author: nxf42811
 */

#ifndef MAIN_H_
#define MAIN_H_

#define BAREMETAL_TO_REGISTERS		0u
#define PINTOOL_TO_REGISTERS		1u

#define GPIO_REGISTERS_INIT		BAREMETAL_TO_REGISTERS


/* Three instruction added after interrupt flag clearing as required */
#define M1_END_OF_ISR \
    {                 \
        __DSB();      \
        __ISB();      \
    }

#endif /* MAIN_H_ */
