//
// Created by rrzhang on 2019/9/10.
//

#ifndef COMPARE_GLUSTER_AND_GPRC_PROFILER_H
#define COMPARE_GLUSTER_AND_GPRC_PROFILER_H

#include <chrono>

class Profiler {
public:
    //! Starts the timer
    void Start() {
        finished_ = false;
        start_ = Tick();
    }
    //! Finishes timing
    void End() {
        end_ = Tick();
        finished_ = true;
    }

    void Suspend(){
        if(!finished_){
            End();
        }
        count_ += std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_);
    }

    //! Returns the elapsed time in seconds. If End() has been called, returns
    //! the total elapsed time. Otherwise returns how far along the timer is
    //! right now.
    double Elapsed() {
        if(!finished_){
            Suspend();
        }
        return double(count_.count());
    }

    double Micros(){
        return Elapsed();
    }

    double Seconds(){
        if(!finished_){
            Suspend();
        }
//        return double(std::chrono::duration_cast<std::chrono::seconds>(count_).count());
        return std::chrono::duration_cast<std::chrono::duration<double>>(count_).count();
    }

    void Clear(){
        count_ = std::chrono::microseconds(0);
    }
private:
    std::chrono::time_point<std::chrono::system_clock> Tick() const {
        return std::chrono::system_clock::now();
    }
    std::chrono::time_point<std::chrono::system_clock> start_;
    std::chrono::time_point<std::chrono::system_clock> end_;
    bool finished_ = false;
    std::chrono::microseconds count_ = std::chrono::microseconds(0);
};

#endif //TEST_SOCKET_PROFILER_H
