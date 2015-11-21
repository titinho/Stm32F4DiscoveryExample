#include <stdio.h>
#include "diag/Trace.h"
#include "bsp.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
	LedOn(LED_ALL);
	while (1)
    {
	  HAL_Delay(500);
       LedToogle(LED_BLUE|LED_GREEN);
    }
}

#pragma GCC diagnostic pop
