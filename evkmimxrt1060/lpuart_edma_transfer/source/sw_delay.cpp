// Source: https://developpaper.com/the-method-of-adding-c-source-files-into-sdk-project-compilation-under-mcuxpresso-ide/

#include "sw_delay.h"

void sw_delay(uint32_t n)
{
    while (n != 0U)
    {
        n--;
    }
}
