#pragma once

#include <array>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <thread>

namespace thrd {

/**
 * @brief thrd::thread is a wrapper for std::thread which adds Linux-specific functions for 
 *        setting/getting the thread name and scheduling policy/priority
 * 
 *        Note: based on https://stackoverflow.com/questions/19422684/stdthread-management-usage-and-best-practice
 */
class thread : private std::thread {
public:
    static constexpr size_t THREAD_NAME_MAX = 15;
    //using std::thread::thread;
    thread() = default;
    thread(thread&&) = default;
    thread& operator=(thread&&) = default;

    ~thread()
    {
        if (joinable()) {
            join(); // could call detach()
        }
    }

    using std::thread::join;
    using std::thread::detach;
    using std::thread::joinable;
    using std::thread::get_id;
    using std::thread::hardware_concurrency;

    void swap(thread& x) { std::thread::swap(x); }

    /**
     * @brief Construct a new thread object specifying a thread name
     * 
     * @tparam Function 
     * @tparam Args 
     * @param f - thread function
     * @param name - thread name
     * @param args - arguments to thread function
     */
    template< class Function, typename... Args >
    explicit thread( Function&& f, const std::string &name, Args&&... args): 
        std::thread(f, std::forward<Args>(args)...) {
        setName(*this,name);
    }

    /**
     * @brief Construct a new thread object specifying a POSIX thread scheduling policy and priority
     * 
     * @tparam Function 
     * @tparam Args 
     * @param f - thread function
     * @param policy - POSIX scheduling policy
     * @param priority - POSIX thread priority
     * @param args - arguments to thread function
     */
    template< class Function, typename... Args >
    explicit thread( Function&& f, int policy, int priority, Args&&... args): 
        std::thread(f, std::forward<Args>(args)...) {
        setScheduling(*this,policy,priority);
    } 

    /**
     * @brief Construct a new thread object specifying a thread name and POSIX thread scheduling policy and priority
     * 
     * @tparam Function 
     * @tparam Args 
     * @param f - thread function
     * @param name - thread name
     * @param policy - POSIX scheduling policy
     * @param priority - POSIX thread priority
     * @param args - arguments to thread function
     */
    template< class Function, typename... Args >
    explicit thread( Function&& f, const std::string &name, int policy, int priority, Args&&... args): 
        std::thread(f, std::forward<Args>(args)...) {
        setName(*this,name);
        setScheduling(*this,policy,priority);
    }    

    /**
     * @brief Get this thread's name
     * 
     * @return std::string 
     */
    std::string getName() {
        return getName(*this);
    }

    /**
     * @brief Get this thread's scheduling parameters and policy
     * 
     * @param policy - POSIX scheduling policy
     * @return sched_param - POSIX scheduling parameters
     */
    sched_param getScheduling(int& policy) {
        return getScheduling(*this,policy);
    }

    /**
     * @brief Set the scheduling policy and parameters for a POSIX thread
     * 
     * @param th - std::thread to be configured
     * @param policy - POSIX scheduling policy
     * @param priority - POSIX thread priority
     */
    static void setScheduling(std::thread &th, int policy, int priority) {
        sched_param schedParams;
        schedParams.sched_priority = priority;
        if (pthread_setschedparam(th.native_handle(), policy, &schedParams) != 0) {
            std::cerr << "Failed to set Thread scheduling: errno " << errno << "\n";
        }
    }

    /**
     * @brief Get the scheduling policy and parameters for a POSIX thread
     * 
     * @param th - std::thread
     * @param policy - POSIX scheduling policy
     * @return sched_param - POSIX scheduling parameters
     */
    static sched_param getScheduling(std::thread &th, int &policy) {
        sched_param schedParams;
        if (pthread_getschedparam(th.native_handle(), &policy, &schedParams) != 0) {
            std::cerr << "Failed to get Thread schedulign: errno " << errno << "\n";
        }
        return schedParams;
    }

    /**
     * @brief Set the name of a POSIX thread
     * 
     * @param th - std::thread
     * @param name - thread name
     */
    static void setName(std::thread &th, const std::string &name) {
        if (pthread_setname_np(th.native_handle(), name.c_str()) != 0) {
            std::cerr << "Failed to set Thread name: errno " << errno << "\n";
        }
    }

    /**
     * @brief Get the name of a POSIX thread
     * 
     * @param th - std::thread
     * @return std::string - thread name
     */
    static std::string getName(std::thread &th) {
        std::array<char,THREAD_NAME_MAX> buf;
        if (pthread_getname_np(th.native_handle(), buf.data(), sizeof(buf)) != 0) {
            std::cerr << "Failed to get Thread name: errno " << errno << "\n";
        }
        return std::string { buf.data() };
    }

};

inline void swap(thread &x, thread &y) {
     x.swap(y);
}

}  // namespace thrd