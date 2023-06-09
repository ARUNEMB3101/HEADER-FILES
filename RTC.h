#ifndef RTC_H
#define RTC_H

#include <I2C.h>
#define RTC_SEC 0x00
#define RTC_MIN 0x01
#define RTC_HR 0x02
#define RTC_DAY 0x03
#define RTC_DAT 0x04
#define RTC_MON 0x05
#define RTC_YR 0x06
#define RTC_OUT 0x07

char rtc_reg[8];

void write_rtc(char *rtc_val)
{
 char rtc_temp,rtc_n;
 i2c_init();
 for(rtc_n=3;rtc_n>0;rtc_n--)
 {
  i2c_start();
  i2c_write(0xD0);
  i2c_write(rtc_n-1);
  rtc_temp=(*rtc_val&0x0F)<<4;
  *rtc_val++;
  rtc_temp=rtc_temp|(*rtc_val&0x0F);
  *rtc_val++;
  i2c_write(rtc_temp);
  *rtc_val++;
  i2c_stop();
 }
 for(rtc_n=3;rtc_n<7;rtc_n++)
 {
  i2c_start();
  i2c_write(0xD0);
  i2c_write(rtc_n);
  rtc_temp=(*rtc_val&0x0F)<<4;
  *rtc_val++;
  rtc_temp=rtc_temp|(*rtc_val&0x0F);
  *rtc_val++;
  i2c_write(rtc_temp);
  *rtc_val++;
  i2c_stop();
 }
}

void write_time(char *rtc_t)
{
 char rtc_tempt,rtc_nt;
 i2c_init();
 for(rtc_nt=3;rtc_nt>0;rtc_nt--)
 {
  i2c_start();
  i2c_write(0xD0);
  i2c_write(rtc_nt-1);
  rtc_tempt=(*rtc_t&0x0F)<<4;
  *rtc_t++;
  rtc_tempt=rtc_tempt|(*rtc_t&0x0F);
  *rtc_t++;
  *rtc_t++;
  i2c_write(rtc_tempt);
  i2c_stop();
 }
}

void write_date(char *rtc_d)
{
 char rtc_tempd,rtc_nd;
 i2c_init();
 for(rtc_nd=4;rtc_nd<7;rtc_nd++)
 {
  i2c_start();
  i2c_write(0xD0);
  i2c_write(rtc_nd);
  rtc_tempd=(*rtc_d&0x0F)<<4;
  *rtc_d++;
  rtc_tempd=rtc_tempd|(*rtc_d&0x0F);
  *rtc_d++;
  *rtc_d++;
  i2c_write(rtc_tempd);
  i2c_stop();
 }
}

void read_rtc()
{
  char rtc_p;
  i2c_init();
  i2c_start();
  i2c_write(0xD0);
  i2c_write(0x00);

  i2c_start();
  i2c_write(0xD1);

  for(rtc_p=0;rtc_p<8;rtc_p++)
  {
   rtc_reg[rtc_p]=i2c_read();
   if(rtc_p!=7)
   {
    i2c_ack();
   }
   else
   {
    i2c_nack();
   }
  }
  i2c_stop();
}

void rtc_out(char rtc_o)
{
 i2c_init();
 i2c_start();
 i2c_write(0xD0);
 i2c_write(0x07);
 i2c_write(rtc_o<<7);
 i2c_stop();
}

void rtc_sqw(char rtc_w)
{
 i2c_init();
 i2c_start();
 i2c_write(0xD0);
 i2c_write(0x07);
 i2c_write(0x10|rtc_w);
 i2c_stop();
}

void rtc_set(char rtc_add,char rtc_value)
{
 i2c_init();
 i2c_start();
 i2c_write(0xD0);
 i2c_write(rtc_add);
 i2c_write(rtc_value);
 i2c_stop();
}

char rtc_get(char rtc_addr)
{
 char rtc_dat;
 i2c_init();
 i2c_start();
 i2c_write(0xD0);
 i2c_write(rtc_addr);
 i2c_start();
 i2c_write(0xD1);
 rtc_dat=i2c_read();
 i2c_nack();
 i2c_stop();
 return rtc_dat;
}

#endif