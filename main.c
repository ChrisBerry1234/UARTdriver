#include <msp430.h>

//define macros 
#define SMCLK  1000000
#define ACLK  32768

//enums for selecting clk
typedef enum{
  SMCLK,
  ACLK
}uart_clk;

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
static void uart_configure_baud(uart_clk clk_select, const uint32_t desired_baud_rate)
{
  //configure clk 
  UCA1CTWLW0 |= clk_select;
  
  //determine prescalar value
  uint16_t prescaler = (clk_select / desired_baud_rate)
  //set prescalar value 
  UCA1BRW = prescaler; 

  //branching to determine low frequency mode
  if (prescaler > 16)
    //enable oversampling 
    UCA1MCTLW |= UC0S16;
  else {
    //no sampling
    UCA1MCTLW - 0xD600;
    //UCA1MCTLW = UC0S16;
    //
  }
}

