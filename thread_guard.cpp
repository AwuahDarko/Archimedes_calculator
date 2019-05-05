#include "thread_guard.h"

thread_guard::~thread_guard()
{
    if(guard.joinable())
    {
        guard.join();
    }
}
