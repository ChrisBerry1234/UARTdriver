#include <msp430.h>

//constants
const RETRY_COUNT = 100;

//define macros 
#define SMCLK  1000000
#define ACLK  32768

//enums for selecting clk
typedef enum{
  uart_clk_SMCLK,
  uart_clk_ACLK,
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
  uint16_t prescaler = 0; 
  
  //configure clk 
  if (clk_select == uart_clk_ACLK)
     UCA1CTWLW0 |= ACLK;
  else 
     UCA1CTWLW0 |= SMCLK;

  //determine prescalar value
  prescaler = (uint16_t)(clk_select / desired_baud_rate);
  //set prescalar value 
  UCA1BRW = prescaler; 

  //branching to determine frequency mode
  if (prescaler > 16)
    //enable oversampling 
    UCA1MCTLW |= UC0S16;
  else {
    //no sampling
    UCA1MCTLW - 0xD600;
  }
}
//ACTION HELPERS
static inline void uart_set_tx_byte(uint8_t byte){UCA1TXBUF = byte;//flag automatically cleared and bit is sent out once it is loaded}
static inline uint8_t uart_get_rx_byte(void){return UCA1RXBUF;}
static inline void uart_clear_tx_buffer_flag(void){ UCA1IFG |= UCTXIFG }

//Status Checkers
static uart_result uart_check_tx_byte(void)
{
  uint16_t retries = RETRY_COUNT;
  //wait until flag is asserted under condition
  while(!(UCA1IFG & UCTXIFG) && retries >= 0){}//keep looping until condition 1 condition is satisfied
  if (retries == 0)
  {
    return UART_RESULT_ERROR_TIMEOUT; 
  }
  return () UART_RESULT_ERROR_CHECK_TX : UART_RESULT_OK;
    
  
}


//init
void uart_init(void)
{
  
}

//PUBLIC API

