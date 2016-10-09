#include <stdio.h>
#include <pigpio.h>

#define GPIO_5 0x00000020
#define GPIO_6 0x00000040
#define GPIO_13 0x00002000
#define GPIO_19 0x00080000

int main(int argc, char* argv[])
{
    unsigned int gpio_read;
    unsigned int gpio_set;

    int iteration = 0;

    double start;

    if(gpioInitialise() < 0)
    {
        fprintf(stderr, "pigpio initialisation failed\n");
        return 1;
    }

    gpioSetMode(5, PI_OUTPUT);
    gpioSetMode(6, PI_OUTPUT);
    gpioSetMode(13, PI_OUTPUT);
    gpioSetMode(19, PI_OUTPUT);

    gpioWrite_Bits_0_31_Clear(GPIO_5 | GPIO_6 | GPIO_13 | GPIO_19);
    gpioWrite_Bits_0_31_Set(GPIO_5);

    start = time_time();
    while((time_time() - start) < 10.0)
    {
        gpio_read = gpioRead_Bits_0_31();
        fprintf(stderr, "gpio_read %d: %lu\n",iteration, gpio_read);

        switch(iteration)
        {
            case 0:
                gpioWrite_Bits_0_31_Set(GPIO_6);
                iteration++;
                break;
            case 1:
                gpioWrite_Bits_0_31_Clear(GPIO_5);
                iteration++;
                break;
            case 2:
                gpioWrite_Bits_0_31_Set(GPIO_13);
                iteration++;
                break;
            case 3:
                gpioWrite_Bits_0_31_Clear(GPIO_6);
                iteration++;
                break;
            case 4:
                gpioWrite_Bits_0_31_Set(GPIO_19);
                iteration++;
                break;
            case 5:
                gpioWrite_Bits_0_31_Clear(GPIO_13);
                iteration++;
                break;
            case 6:
                gpioWrite_Bits_0_31_Set(GPIO_5);
                iteration++;
                break;
            case 7:
                gpioWrite_Bits_0_31_Clear(GPIO_19);
                iteration = 0;
                break;
        }
        time_sleep(0.5);
    }

    gpioTerminate();

    return 0;
}
