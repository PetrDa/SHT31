//
//    FILE: SHT31_async.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.0.2
// PURPOSE: demo async interface
//

#include "Wire.h"
#include "SHT31.h"

uint32_t start;
uint32_t stop;
uint32_t cnt;

SHT31 sht;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT31_LIB_VERSION: \t");
  Serial.println(SHT31_LIB_VERSION);

  Wire.begin();
  sht.begin(0x44);
  Wire.setClock(100000);

  uint16_t stat = sht.readStatus();
  Serial.print(stat, HEX);
  Serial.println();
  
  sht.requestData();
  cnt = 0;
}

void loop()
{
  if (sht.dataReady())
  {
    start = micros();
    sht.readData();         // default = true = fast       slow = false
    stop = micros();
    sht.requestData();      // request for next sample
		
    Serial.print("\t");
    Serial.print(stop - start);
    Serial.print("\t");
    Serial.print(sht.getTemperature(), 1);
    Serial.print("\t");
    Serial.print(sht.getHumidity(), 1);
    Serial.print("\t");
    Serial.println(cnt);
	cnt = 0;
  }
  cnt++; // simulate activity
}

// -- END OF FILE --