

#define MAX_EVENTS 10

class Timer
{
public:
   Timer() {}
   ~Timer() {}

   // Reset all event trigger times to 'now' without executing the callbacks.
   void reset();

   // Create a new event that triggers every 'period' mS and executes
   // the 'callback' specified.
   int every(unsigned long period, void (*callback)(void));

   // Change the frequency that the event gets triggered:
   void updatePeriod(int event, unsigned long period);

   // Disable the specified event without deleting it.
   void pause(int event);

   // Enable the specified event if it was disabled.
   void resume(int event);

   // Process all of the events, executing callbacks if periods have elapsed.
   void process();

private:
   // Container holding event info
   struct Event
   {
      Event()
      {
         _active = false;
         _callback = 0;
      }
      ~Event() {}
      bool _active;
      void (*_callback)(void);
      unsigned long _period;
      unsigned long _lastMillis;
   };

   // Set of events that this Timer is managing:
   Event _events[MAX_EVENTS];
};
