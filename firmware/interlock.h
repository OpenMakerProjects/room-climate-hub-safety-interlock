#pragma once
#include <stdint.h>
struct Interlock {
 bool armed=false,latched=false; uint32_t safeSince=0;
 void update(uint32_t now,bool warm,bool motion,bool loud,bool valid){
  if(!warm || !valid || motion || loud){
   if(armed)latched=true;
   armed=false;safeSince=now;
  }
 }
 bool arm(uint32_t now,bool warm,bool safe){
  if(!warm||!safe||uint32_t(now-safeSince)<3000)return false;
  latched=false;armed=true;return true;
 }
 void stop(){armed=false;latched=true;}
};
