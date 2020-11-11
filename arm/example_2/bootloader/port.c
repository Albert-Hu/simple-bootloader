#include <stdint.h>
#include <errno.h>
#include <sys/stat.h>
#include "reg.h"

#define USART_FLAG_TXE	((uint16_t) 0x0080)

extern char _heap_begin;
extern char _heap_end;

int _close(int file)
{
  return -1;
}

int _fstat(int file, struct stat* st)
{
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int file)
{
  return 1;
}

int _lseek(int file, int ptr, int dir)
{
  return 0;
}

int _open(const char* name, int flags, int mode)
{
  return -1;
}

int _read(int file, char* ptr, int len)
{
  return -1;
}

caddr_t _sbrk(int incr)
{
  static char* current_heap_end;
  char* current_block_address;

  if (current_heap_end == 0) {
    current_heap_end = &_heap_begin;
  }

  current_block_address = current_heap_end;

  // Need to align heap to word boundary, else will get
  // hard faults on Cortex-M0. So we assume that heap starts on
  // word boundary, hence make sure we always add a multiple of
  // 4 to it.
  incr = (incr + 3) & (~3); // align value to 4
  if (current_heap_end + incr > &_heap_end) {
    // Heap has overflowed
    errno = ENOMEM;
    return (caddr_t) - 1;
  }

  current_heap_end += incr;
  return (caddr_t) current_block_address;
}

int _write(int file, char* ptr, int len)
{
  int i;
  for (i = 0; i < len; i++) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (ptr[i] & 0xFF);
	}
  return len;
}
