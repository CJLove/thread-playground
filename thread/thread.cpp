
#include "Thread.h"
#include <iostream>
#include <chrono>
#include <mutex>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

using thrd::thread;
using namespace std::chrono_literals;

static std::mutex logMutex;

void thread1Func() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Starting thread1\n";
    }

    while (true) {
        std::this_thread::sleep_for(15s);
        {
            std::lock_guard<std::mutex> guard(logMutex);
            std::cout << "Hello from thread1\n";
        }
    }
}

void thread2Func() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Starting thread2\n";
    }

    while (true) {
        std::this_thread::sleep_for(20s);
        {
            std::lock_guard<std::mutex> guard(logMutex);
            std::cout << "Hello from thread2\n";
        }
    }
}

void thread3Func() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Starting thread3\n";
    }

    while (true) {
        std::this_thread::sleep_for(60s);
        {
            std::lock_guard<std::mutex> guard(logMutex);
            std::cout << "Hello from thread3\n";
        }
    }    
}

std::ostream &dumpPolicy(int policy, std::ostream &os) {
    switch (policy) {
    case SCHED_BATCH:
        os << "SCHED_BATCH";
        break;
    case SCHED_RR:
        os << "SCHED_RR";
        break;
    case SCHED_FIFO:
        os << "SCHED_FIFO";
        break;
    case SCHED_OTHER:
        os << "SCHED_OTHER";
        break;
    default:
        break;
    }
    return os;
}

std::ostream &dumpLimit(rlim_t limit, std::ostream &os) {
    if (limit == RLIM_INFINITY) {
        os << "unlimited";
    }
    else {
        os << limit;
    }
    return os;
}

int main(int /* argc */, char** /* argv */) {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    std::cout << "Process pid " << pid << " ppid " << ppid << "\n";

    // Display rtprio limits
    struct rlimit limit;
    getrlimit(RLIMIT_RTPRIO, &limit);
    std::cout << "rlim_cur ";
    dumpLimit(limit.rlim_cur, std::cout);
    std::cout << " rlim_max ";
    dumpLimit(limit.rlim_max, std::cout);
    std::cout << "\n";

    std::thread thread1(thread1Func);
    thread::setName(thread1, "MyRRThread");
    thread::setScheduling(thread1, SCHED_RR, 90);

    std::thread thread2(thread2Func);
    thread thread3(thread3Func,"MyOtherThread");

    thread::setName(thread2, "MyFIFOThread");

    thread::setScheduling(thread2, SCHED_FIFO, 50);


    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Thread 1 tid " << thread1.get_id() << " name " << thread::getName(thread1) <<  "\n";
        std::cout << "Thread 2 tid " << thread2.get_id() << " name " << thread::getName(thread2) << "\n";
        std::cout << "Thread 3 tid " << thread3.get_id() << " name " << thread3.getName() << "\n";
    }

    int policy;
    sched_param parms = thread::getScheduling(thread1,policy);
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Thread 1 policy "; 
        dumpPolicy(policy,std::cout);
        std::cout << " priority " << parms.sched_priority << "\n";
    }

    parms = thread::getScheduling(thread2,policy);
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Thread 2 policy "; 
        dumpPolicy(policy,std::cout);
        std::cout << " priority " << parms.sched_priority << "\n";
    }

    parms = thread3.getScheduling(policy);
    {
        std::lock_guard<std::mutex> guard(logMutex);
        std::cout << "Thread 3 policy "; 
        dumpPolicy(policy,std::cout);
        std::cout << " priority " << parms.sched_priority << "\n";
    }    

    std::flush(std::cout);

    while (true) {
        std::this_thread::sleep_for(60s);
    }
}