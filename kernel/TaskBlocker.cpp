
#include "TaskBlocker.h"
#include "drivers/PIT.h"
#include "asserts.h"
#include "Scheduler.h"


bool SleepBlocker::can_unblock() {
    auto sec = PIT::seconds_since_boot();
    auto ms = PIT::ticks_this_second();
    if(sec < m_sleep_until_sec) {
        return false;
    }
    // we can skeep at most a single second
    
    // we can skip a single second if
    // SleepBlocker::can_unblock()
    // was called once at (e.g) 1.999sec,
    // and then at 2.001sec
    
    ASSERT(sec - m_sleep_until_sec <= 1);
    return sec > m_sleep_until_sec || ms >= m_leftover_ms;
}

WaitBlocker::WaitBlocker()
    : TaskBlocker()
    {}

bool WaitBlocker::can_unblock()
{
    return m_waitee_finished;
}