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
  UART_RESULT_ERROR_TIMEOUT_TX,
  UART_RESULT_ERROR_TIMEOUT_RX,
  UART_RESULT_OK,
  UART_RESULT_ERROR_CHECK_TX, 
  UART_ERROR_INVALID_PARAM,
}uart_result;


int main(void)
{

return 0;
}

//PUBLIC APIs
uart_result uart_transmit_byte(const uint8_t *data);
uart_result uart_receive_byte(const uint8_t *data);

//wrapper functions
uart_result uart_transmit_16_bit_string(const uint)
{
  return 
};
uart_result uart_transmit_32_bit_string(const uint );

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

//STATUS CHECKERS
static uart_result uart_check_tx_buffer(void)
{
  uint16_t retries = RETRY_COUNT;
  //wait until flag is asserted under condition
  while(!(UCA1IFG & UCTXIFG) && retries >= 0){}//keep looping until condition 1 condition is satisfied
  if (retries == 0)
  {
    return UART_RESULT_TX_ERROR_TIMEOUT; 
  }
  --retries,
  return (UCA1STATW & (UCFE | UCOE)) ? UART_RESULT_ERROR_CHECK_TX : UART_SUCCESS;
}

static uart_result uart_check_rx_byte(void)
{
  uint16_t retries = RETRY_COUNT;
  while(!(UCA1IFG & UCRXIFG) && --retries)
  if (retries == 0)
  {
    return UART_RESULT_RX_ERROR_TIMEOUT; 
  }
  if (UCA1STATW & (UCFE | UCOE)) {
    //ERROR IN BIT TRANSMISSION, TO REMOVE BAD DATA, RXBUF MUST BE CLEAR OR MANUALLY GO INTO SOFTWARE RESET
    volatile uint16_t stale_data = UCA1RXBUF;  
    return UART_RESULT_ERROR_CHECK_RX
}
return UART_RESULT_OK;
}


//init
void uart_init()
{
  --SETUP UART A1
  UCA1CTLW0 |= UCSWRST;  //puts UART A1 into SW reset

  P4SEL1 &= ~BIT3;       // Set P4.3 to use UART A1 Tx function
  P4SEL0 |= BIT3;

  //ADD UART baudconfiguration here
 //uart_configure_baud(uart_clk clk_select, const uint32_t desired_baud_rate);

  //clear reset
  UCA1CTLW0 |= UCSWRST;  //puts UART A1 into SW reset
}

//PUBLIC API
uart_result uart_transmit_byte(const uint8_t *data)
{
  uart_result result = uart_check_tx_byte(); 
  if (result)
  {
    return result; 
  }
  uart_set_tx_byte(*data);
  return 
}

uart_result uart_transmit_string(const uint16_t string_size, const char *string )
{

    if (string == NULL || string_size == 0)
    {
      return UART_ERROR_INVALID_PARAM;
    }
  
    UCA1IE |= UCTXCPTIE;              // enable Tx complete interrupt
    UCA1IFG &= ~UCTXCPTIFG;           // clear Tx complete flag

    uart_result result = uart_check_tx_byte();
    if (result)
    {
      return result;
    }

    //IF ALL CLEAR BEGIN DATA TRANSFER 
    for (uint32_t = 1; i<string_size; i++)
      {

        //THERE ARE SOME ERRORS THAT WE MAY WANT TO CHECK EARLY
        if (string[i] == '\0') 
        {
          break;
        }

        //wait for TX hardware buffer 
        result = uart_check_tx_byte();
        if(result != UART_RESULT_OK)
        {
          return result; 
        }
        uart_set_tx_byte(string[i]);
    }
        // Wait until the final bit physically leaves the shift register
        // before turning off flags or leaving the function context
        while (!(UCA1IFG & UCTXCPTIFG)){}; 
  
        return UART_RESULT_OK;
  }

   
}
