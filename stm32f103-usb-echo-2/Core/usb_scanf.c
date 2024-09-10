// file usb_scanf.c
#include "usb_scanf.h"

FIFO RX_FIFO =
{
  .head=0, .tail=0
  //.data[FIFO_SIZE];
};

// returns bytes read (could be zero)
// would be easy to make it end early on a stop char (e.g., \r or \n)
// returns bytes read (could be zero)
// would be easy to make it end early on a stop char (e.g., \r or \n)
uint8_t VCP_read(uint8_t* Buf, uint32_t Len)
{
  uint32_t count=0;

  if ((Buf == NULL) || (Len == 0))
  {
    return 0;
  }

  while (Len--)
  {
    if (RX_FIFO.head == RX_FIFO.tail) return count;

    if (RX_FIFO.data[RX_FIFO.tail] == '\r' || RX_FIFO.data[RX_FIFO.tail] == '\n')
    {
      *Buf = '\0';
      RX_FIFO.tail++;
      if (RX_FIFO.tail >= FIFO_SIZE) RX_FIFO.tail -= FIFO_SIZE;

      break;
    }

    count++;
    *Buf++=RX_FIFO.data[RX_FIFO.tail];
    RX_FIFO.tail=FIFO_INCR(RX_FIFO.tail);
  }

  return count;
}
