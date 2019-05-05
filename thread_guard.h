#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

class thread_guard
{
public:
    explicit thread_guard(std::thread& t):guard{t} {}
    ~thread_guard();
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
private:
    std::thread& guard;
};

#endif // THREAD_GUARD_H
