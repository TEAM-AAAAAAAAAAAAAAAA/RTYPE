/*
** EPITECH PROJECT, 2022
** RTYPE
** File description:
** LockedQueue
*/

#pragma once
#include <list>
#include <mutex>
#include <queue>

/**
 * Simple mutex-guarded queue
 */
namespace network
{
     /**
     * Standard pair class that contains a string and the ID of the client that
     * sent it
     */
    typedef std::array<char, 16> Message;
    typedef std::pair<Message, unsigned int> ClientMessage;
    typedef std::pair<Message, std::vector<unsigned int>> ServerMessage;

    template <typename T> class LockedQueue {
      private:
        /**
         * Standard mutex class which lets us lock the queue
         */
        std::mutex mutex;
        /**
         * Templated standard queue class which lets us use the queue with any
         * class
         */
        std::queue<T> queue;

      public:
        /**
         * Function which pushes the value into the queue while locking it
         * @param value value to push
         */
        void push(T value)
        {
            std::unique_lock<std::mutex> lock(mutex);
            queue.push(value);
        };

        /**
         * Get the top value of the queue
         *  @return return the front value
         */
        T pop()
        {
            std::unique_lock<std::mutex> lock(mutex);
            T value;
            std::swap(value, queue.front());
            queue.pop();
            return value;
        };

        /**
         * Check if the queue is empty
         * @return True if queue is empty
         */
        bool empty()
        {
            std::unique_lock<std::mutex> lock(mutex);
            return queue.empty();
        }
    };
}