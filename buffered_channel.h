#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#include<queue>
#include<iostream>
#include <mutex>
#include <condition_variable>


template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size): buffer_size(size), is_open(true) {}

    void Send(T value) {
        if (!is_open) {
            throw std::runtime_error("Channel is close");
        }
        std::unique_lock<std::mutex> lock(g_lockqueue);
        g_queuecheck.wait(lock, [this]() {
            return queue.size() != buffer_size || is_open;
            });

        queue.push(value);
        lock.unlock();
        g_queuecheck.notify_all();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(g_lockqueue);
        g_queuecheck.wait(lock, [this]() {
            return queue.size() != buffer_size || is_open;
            });

        T tmp;
        if (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
        }

        lock.unlock();
        g_queuecheck.notify_all();

        return std::pair<T,bool>(tmp, is_open);
    }

    void Close() {
        std::unique_lock<std::mutex> lock(g_lockqueue);
        is_open = false;
        lock.unlock();
        g_queuecheck.notify_all();
    }

private:

    std::queue<T>           queue;
    std::mutex              g_lockqueue;
    std::condition_variable g_queuecheck;
    bool                    is_open;
    int                     buffer_size;
};

#endif // BUFFERED_CHANNEL_H_
