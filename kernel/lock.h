#pragma once
#include "types.h"
#include "NonCopyable.h"

class Lock
{
NON_COPYABLE(Lock)
public:
    Lock(const char* name) : m_name(name){}
    void lock();
    void unlock();

private:
    u32 m_locked {0};
    const char* m_name = nullptr;
    u32 m_flags {0};
};

class Locker
{
NON_COPYABLE(Locker)
public:
    Locker(Lock& lock);
    ~Locker();

private:
    Lock& m_lock;
};

#define LOCKER(lock) Locker locker(lock)

class RealLock
{
NON_COPYABLE(RealLock)
public:
    RealLock(const char* name) : m_name(name){}
    void lock();
    void unlock();

private:
    u32 m_locked {0};
    const char* m_name = nullptr;
};

class RealLocker
{
NON_COPYABLE(RealLocker)
public:
    RealLocker(RealLock& lock);
    ~RealLocker();

private:
    RealLock& m_lock;
};

#define REAL_LOCKER(lock) RealLocker locker(lock)