/*
 * @file    TaskProcessor.h
 * @author  Lukasz Rachwalski
 * @date    20/02/2018
 * @version 1.0
 *
 * @brief   Exemplary implementation of task processor.
 */

#pragma once

#include "BlockingQueue.h"
#include <functional>
#include <vector>
#include <future>

/*
 *  @brief Task processor implementation class.
 *
 */

template<
    typename Task = std::function<void()>,
    typename Queue = BlockingQueue<Task>
>
class TaskProcessor {
    Queue queue;
    std::vector< std::future<void> > consumers;
public:
    
    /*
     *  @brief Task processor constructor. It creates consumer threads.
     *
     *  @param numberOfConsumers is a number of consumer threads processing enqueued tasks.
     */
    
    explicit TaskProcessor(const std::size_t numberOfConsumers = std::thread::hardware_concurrency())
    : queue{numberOfConsumers} {
        
        for(std::size_t i=0; i< numberOfConsumers; ++i) {
            
            consumers.emplace_back(
                std::async( std::launch::async,
                   [this] {
                       while(true) {
                           queue.Pop()();
                       }
                   })
           );
            
        }
        
    }
    
    /*
     *  @brief Task processor destructor. It terminates blocked consumer and producer threads.
     */
    
    ~TaskProcessor() {
        queue.Abort();
    }
    
    /*
     *  @brief Function enqueues new task to be processed asynchronously.
     *
     *  @param task is a Task type value inserted to queue.
     */
    
    void Post(Task&& task) {
        queue.Push(std::move(task));
    }
};
