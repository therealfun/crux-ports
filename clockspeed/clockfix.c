#include <sys/time.h>
#include <unistd.h>

double nano(buf)
unsigned char buf[16];
{
  unsigned long u;
  double result;

  /* XXX: ignoring buf[0...3] */

  u = buf[12];
  u <<= 8; u += buf[13];
  u <<= 8; u += buf[14];
  u <<= 8; u += buf[15];
  result = u * 0.000000001;

  u = buf[8];
  u <<= 8; u += buf[9];
  u <<= 8; u += buf[10];
  u <<= 8; u += buf[11];
  result += u;

  u = buf[4];
  u <<= 8; u += buf[5];
  u <<= 8; u += buf[6];
  u <<= 8; u += buf[7];
  if (u < 2147483648UL)
    result += 1000000000.0 * u;
  else
    result += 0.0 - 1000000000.0 * (4294967295UL + 1 - u);

  return result;
}

void main()
{
  int r;
  double deriv;
  struct timeval tvchange;
  unsigned char buf[16];

  r = read(0,buf,sizeof buf);
  if (r <= 0) _exit(1); /* not possible */
  deriv = nano(buf);

  deriv *= 0.001;
  if (deriv > 99999999.0) deriv = 99999999.0;
  if (deriv < -99999999.0) deriv = -99999999.0;

  tvchange.tv_sec = 0;
  tvchange.tv_usec = deriv;
  while (tvchange.tv_usec < 0) {
    tvchange.tv_sec -= 1;
    tvchange.tv_usec += 1000000;
  }
  while (tvchange.tv_usec > 999999) {
    tvchange.tv_sec += 1;
    tvchange.tv_usec -= 1000000;
  }

  adjtime(&tvchange,(struct timeval *) 0);

  for (;;) {
    sleep(10);
    adjtime((struct timeval *) 0, &tvchange);
    if (tvchange.tv_sec == 0 && tvchange.tv_usec == 0)
      _exit(0);
  }
}
