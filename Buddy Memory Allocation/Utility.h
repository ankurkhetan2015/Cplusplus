#ifndef UTILITY_H_
#define UTILITY_H_

typedef unsigned int uint;

uint power_of_two(uint number)
{
    uint result;
    if (number > 0 && ((number & (number - 1)) == 0))
    {
        result = number;
    }
    else
    {
        result = number;
        result--;
        result |= result >> 1;
        result |= result >> 2;
        result |= result >> 4;
        result |= result >> 8;
        result |= result >> 16;
        result++;
    }
    return result;
}

#endif /* UTILITY_H_ */
