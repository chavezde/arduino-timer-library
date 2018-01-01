#include "Arduino.h"
#include "Timer.h"


void Timer::reset()
{
   unsigned long now = millis();
   for (int i=0; i<MAX_EVENTS; ++i) {
      if (_events[i]._active) {
         _events[i]._lastMillis = now;
      }
   }
}


int Timer::every(unsigned long period, void (*callback)(void))
{
   for (int i=0; i<MAX_EVENTS; ++i) {
      if (!_events[i]._active) {
         _events[i]._active = true;
         _events[i]._callback = callback;
         _events[i]._period = period;
         _events[i]._lastMillis = millis();
         return i;
      }
   }
   return -1;
}

void Timer::updatePeriod(int event, unsigned long period)
{
   if (event>=0 && event<MAX_EVENTS) {
      _events[event]._period = period;
   }
}


void Timer::pause(int event)
{
   if (_events[event]._active) {
      _events[event]._active = false;
   }
}


void Timer::resume(int event)
{
   if (!_events[event]._active && _events[event]._callback!=0) {
      _events[event]._active = true;
      _events[event]._lastMillis = millis();
   }
}


void Timer::process()
{
   unsigned long now = millis();
   for (int i=0; i<MAX_EVENTS; ++i) {
      if (_events[i]._active &&
          now-_events[i]._lastMillis >= _events[i]._period) {
         (*_events[i]._callback)();
         _events[i]._lastMillis = now;
      }
   }
}
