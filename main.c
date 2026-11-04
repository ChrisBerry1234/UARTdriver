#include <msp430.h>

//define macros 
#define SMCLK  1000000
#define ACLK  32768

//enums for selecting clk
typedef enum{
  SMCLK,
  ACLK
}uart_CLK;

//enum for determining error type result
typedef enum{

}uart_result;



int main(void)
{

return 0;
}

//PUBLIC APIs
uart_result uart_transmit_byte(const uint8_t *data);
uart_result uart_receive_byte(const uint8_t data);

//wrapper functions
//helper functions
static inline 

