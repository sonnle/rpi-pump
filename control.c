#include <stdio.h>
#include <pigpio.h>

#define GPIO_5 0x00000020
#define GPIO_6 0x00000040
#define GPIO_13 0x00002000
#define GPIO_19 0x00080000

int main(int argc, char* argv[])
{
    unsigned int gpio_read, gpio_set;
    int iteration = 0;

    double start;

    if(gpioInitialise() < 0) {
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
    while((time_time() - start) < 20.0) {
#ifdef DEBUG
        gpio_read = gpioRead_Bits_0_31();
        fprintf(stdout, "Read from gpio_read %d: %lu\n",iteration, gpio_read);
#endif
        if((time_time() - start) < 10.0) {
            StepperMotor_StepForward(&iteration);
        }
        else {
            StepperMotor_StepBackward(&iteration);
        }

        if(iteration >= 8) {
            iteration = 0;
        }
        else if(iteration <= -1) {
            iteration = 7;
        }

        time_sleep(0.5);
    }
    gpioTerminate();

    return 0;
}

int StepperMotor_StepForward(int *iteration)
{
    switch(*iteration) {
        case 0:
            gpioWrite_Bits_0_31_Set(GPIO_6);
            break;
        case 1:
            gpioWrite_Bits_0_31_Clear(GPIO_5);
            break;
        case 2:
            gpioWrite_Bits_0_31_Set(GPIO_13);
            break;
        case 3:
            gpioWrite_Bits_0_31_Clear(GPIO_6);
            break;
        case 4:
            gpioWrite_Bits_0_31_Set(GPIO_19);
            break;
        case 5:
            gpioWrite_Bits_0_31_Clear(GPIO_13);
            break;
        case 6:
            gpioWrite_Bits_0_31_Set(GPIO_5);
            break;
        case 7:
            gpioWrite_Bits_0_31_Clear(GPIO_19);
            break;
    }
    (*iteration)++;
#if DEBUG
    fprintf(stdout, "Iteration after increment is: %d\n", *iteration);
#endif
    return 0;
}

int StepperMotor_StepBackward(int *iteration)
{
    switch(*iteration) {
        case 0:
            gpioWrite_Bits_0_31_Set(GPIO_19);
            break;
        case 1:
            gpioWrite_Bits_0_31_Clear(GPIO_6);
            break;
        case 2:
            gpioWrite_Bits_0_31_Set(GPIO_5);
            break;
        case 3:
            gpioWrite_Bits_0_31_Clear(GPIO_13);
            break;
        case 4:
            gpioWrite_Bits_0_31_Set(GPIO_6);
            break;
        case 5:
            gpioWrite_Bits_0_31_Clear(GPIO_19);
            break;
        case 6:
            gpioWrite_Bits_0_31_Set(GPIO_13);
            break;
        case 7:
            gpioWrite_Bits_0_31_Clear(GPIO_5);
            break;
    }
    (*iteration)--;
#if DEBUG
    fprintf(stdout, "Iteration after decrement is: %d\n", *iteration);
#endif
    return 0;
}
