/*
 * @file    BlockingQueue.h
 * @author  Lukasz Rachwalski
 * @date    20/02/2018
 * @version 1.0
 *
 * @brief   Exemplary implementation of blocking queue.
 */

#pragma once

#include <queue>
#include <condition_variable>

/*
 *  @brief Exception type that is thrown when processing queue is aborted.
 *
 */

struct BlockingQueueAborted
    : std::runtime_error {
    BlockingQueueAborted() : std::runtime_error{"BlockingQueue aborted"} {}
};

/*
 *  @brief Blocking queue implementation class.
 *
 */

template<
    typename T,
    typename Queue = std::queue<T>
> class BlockingQueue {
    const std::size_t maxSize;
    bool abort{false};
    mutable std::mutex mutex;
    std::condition_variable onValuePoped;
    std::condition_variable onValuePushed;
    Queue queue;
public:
    
    /*
     *  @brief Blocking queue constructor.
     *
     *  @param maxSize is a maximum number of elements stored in queue.
     */
    
    explicit BlockingQueue(const std::size_t maxSize = 10)
    : maxSize{maxSize} {
    }
    
    /*
     *  @brief Function adds new element to queue. If queue is full, this
     *  function blocks the caller until some element is popped or 'Abort()'
     *  is called.
     *
     *  @param value is an element that is added to queue.
     */
    
    void Push(T&& value) {
        std::unique_lock<std::mutex> lock(mutex);
        
        onValuePoped.wait(lock, [this]()
        {
            if (!abort) {
                return maxSize > queue.size();
            }
            else {
                throw BlockingQueueAborted{};
            }
        });
        
        queue.push(std::move(value));
        onValuePushed.notify_all();
    }
    
    /*
     *  @brief Function removes first element from queue. If queue is empty, this
     *  function blocks the caller until some element is pushed or 'Abort()'
     *  is called.
     *
     *  @return T type value that is removed from queue.
     */
    
    T Pop() {
        std::unique_lock<std::mutex> lock(mutex);
        
        onValuePushed.wait(lock, [this]()
        {
            if (!abort || (abort && !queue.empty())) {
                return !queue.empty();
            }
            else {
                throw BlockingQueueAborted{};
            }
        });
        
        auto value = std::move(queue.front());
        queue.pop();
        onValuePoped.notify_all();
        return value;
    }
    
    /*
     *  @brief Function terminates blocked threads.
     */
    
    void Abort() {
        std::unique_lock<std::mutex> lock(mutex);
        
        abort = true;
        onValuePoped.notify_all();
        onValuePushed.notify_all();
    }
};
