#ifndef _BLINK_PROCESS_
#define _BLINK_PROCESS_

#include <ProcessScheduler.h>
#include <Arduino.h>
/**
* @description Класс для процесса
*
*/
class BlinkProcess : public Process
{
    bool enable = false;

  public:
    // Call the Process constructor
    BlinkProcess(Scheduler &manager, ProcPriority pr, unsigned int period, const char *password = "")
        : Process(manager, pr, period)
    {
    }

  protected:
    virtual void setup()
    {
        Serial.println("Blink Process started");
    }

    // Undo setup()
    virtual void cleanup()
    {
    }

    // Create our service routine
    virtual void service()
    {
        enable = !enable;
        digitalWrite(D0, enable ? HIGH : LOW);
    }
};
#endif
