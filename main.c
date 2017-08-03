#include "main.h"

int main(void) {
  USART_init();
  asm("sei");
  while (1) {
    DDRB |= 0x01;
    unsigned char key[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};
    unsigned char msg[] = "0123456789ABCDE";
    serpent_ctx_t ctx;

    serpent_init(key, 256, &ctx);
    USART_tx_buf_put(msg, 16);
    serpent_enc(msg, &ctx);
    USART_tx_buf_put(msg, 16);
    PORTB |= 0x01;
    serpent_dec(msg, &ctx); // 20 ms @ 16MHz
    PORTB &= ~0x01;
    USART_tx_buf_put(msg, 16);
    _delay_ms(5000);
  }
  return 0;
}