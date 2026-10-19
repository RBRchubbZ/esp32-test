#include <stdio.h>
#include <stdint.h>

int main()
{

    const READ = 0x00;
    const WRITE = 0x01;
//Frame 
struct frame
{ //default int change later
    int serial_;
    int action;
    int data;
}


    return 0;
}

//https://help.campbellsci.com/atmosvue30/shared/example-c-code-ccitt-crc.htm?TocPath=_____10
unsigned int CRC_CCITT(char LineOfData[])
{

unsigned int crc;
// returned CRC value unsigned int i;
// counter crc = 0x0000;
// create a check sum for the incoming data for(i=0;i < strlen(LineOfData); i++)
{

unsigned crc_new = (unsigned char)(crc >> 8) | (crc << 8);
crc_new ^= LineOfData[i];
crc_new ^= (unsigned char)(crc_new & 0xff) >> 4;
crc_new ^= crc_new << 12;
crc_new ^= (crc_new & 0xff) << 5; crc = crc_new;
}

return(crc);

}
//https://stackoverflow.com/questions/17196743/crc-ccitt-implementation
unsigned short crc16(char *ptr, int count)
{
   int  crc;
   char i;
   crc = 0;
   while (--count >= 0)
   {
      crc = crc ^ (int) *ptr++ << 8;
      i = 8;
      do
      {
         if (crc & 0x8000)
            crc = crc << 1 ^ 0x1021;
         else
            crc = crc << 1;
      } while(--i);
   }
   return (crc);
}

//https://industrialmonitordirect.com/blogs/knowledgebase/framing-and-serialization-protocols-for-embedded-serial
uint16_t crc16_ccitt(const uint8_t *buf, size_t len) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= (uint16_t)buf[i] << 8;
        for (int b = 0; b < 8; b++)
            crc = (crc & 0x8000) ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}