#ifndef VIDEO_QUE_H
#define VIDEO_QUE_H

#include <mutex>
#include <deque>
#include <condition_variable>


template<typename T>
class my_ts_que
{
    bool process_finished = false;
    std::mutex m;
    std::deque<T> q;
    std::condition_variable cv_hi, cv_lo;
public:
    bool is_finished() {
        std::lock_guard<std::mutex> lg{m};
        return process_finished;
    }

    void mark_as_finished() {
        std::lock_guard<std::mutex> lg{m};
        process_finished = true;
    }

    size_t get_size() {
        std::lock_guard<std::mutex> lg{m};
        return q.size();
    }

    T pop() {
        std::unique_lock<std::mutex> lg{m};
        while(q.empty())
            cv_lo.wait(lg);
        auto r = q.back();
        q.pop_back();
        return r;
    }

    void push(T &x) {
        {
            std::lock_guard<std::mutex> lg{m};
            q.push_front(x);
        }
        cv_lo.notify_one();
    }

    void push_back(T &x) {
        {
            std::lock_guard<std::mutex> lg{m};
            q.push_back(x);
        }
        cv_lo.notify_one();
    }
};

#endif //VIDEO_QUE_H
