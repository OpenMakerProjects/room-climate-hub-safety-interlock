#include "../firmware/interlock.h"
#include <cassert>
#include <iostream>
int main(){
 Interlock x;x.update(0,false,false,false,true);assert(!x.arm(5000,false,true));
 x.update(60000,true,true,false,true);assert(!x.arm(62000,true,true));
 assert(x.arm(63000,true,true));x.update(63100,true,false,true,true);assert(!x.armed&&x.latched);
 assert(!x.arm(65000,true,true));assert(x.arm(66100,true,true));
 x.update(66200,true,false,false,false);assert(!x.armed&&x.latched);
 assert(x.arm(69200,true,true));x.stop();assert(!x.armed&&x.latched);
 assert(x.arm(72200,true,true));x.update(72300,true,true,false,true);assert(!x.armed&&x.latched);
 Interlock wrap;wrap.safeSince=0xfffffff0u;assert(wrap.arm(0x1000,true,true));
 std::cout<<"warm-up, stable-safe arm, sound/PIR/invalid trip, stop, rearm and timer wrap passed\n";
}
