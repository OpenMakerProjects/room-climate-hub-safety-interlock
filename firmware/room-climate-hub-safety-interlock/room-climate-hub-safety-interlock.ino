#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../interlock.h"
SoftwareSerial ble(12,13); // RX D6 <- HM10 TX, TX D7 -> HM10 RX
Interlock guard;
uint32_t lastSample=0;bool warm=false,safe=false;char command[16];uint8_t used=0;
void handle(char c){
 if(c=='\r')return;
 if(c=='\n'){
  command[used]=0;
  if(!strcmp(command,"ARM"))guard.arm(millis(),warm,safe);
  else if(!strcmp(command,"STOP"))guard.stop();
  used=0;return;
 }
 if(used<sizeof(command)-1)command[used++]=c;else used=0;
}
void setup(){
 pinMode(4,OUTPUT);digitalWrite(4,LOW); // D2 permission LED only
 pinMode(14,INPUT); // D5 PIR
 Serial.begin(115200);ble.begin(9600);
}
void loop(){
 while(ble.available())handle(char(ble.read()));
 uint32_t now=millis();
 if(uint32_t(now-lastSample)<100){delay(1);return;}lastSample=now;
 int lo=1023,hi=0;bool valid=true;
 for(int i=0;i<64;i++){int v=analogRead(A0);lo=min(lo,v);hi=max(hi,v);if(v<2||v>1021)valid=false;delayMicroseconds(100);}
 warm=now>=60000;bool motion=digitalRead(14)==HIGH,loud=hi-lo>=180;safe=valid&&!motion&&!loud;
 guard.update(now,warm,motion,loud,valid);
 digitalWrite(4,guard.armed?HIGH:LOW);
 char line[180];snprintf(line,sizeof(line),"{\"id\":9,\"warm\":%s,\"motion\":%s,\"sound_pp\":%d,\"valid\":%s,\"armed\":%s,\"latched\":%s}",
 warm?"true":"false",motion?"true":"false",hi-lo,valid?"true":"false",guard.armed?"true":"false",guard.latched?"true":"false");
 static uint32_t reported=0;if(uint32_t(now-reported)>=1000){reported=now;Serial.println(line);ble.println(line);}
}
