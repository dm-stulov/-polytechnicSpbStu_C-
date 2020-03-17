#ifndef PRIORITY_QUEUE_IMPLEMENT_HPP
#define PRIORITY_QUEUE_IMPLEMENT_HPP

#include "priority-queue.hpp"

template <typename T>
void PriorityQueue<T>::add(PriorityQueue::Priority priority, const T &element)
{
  switch(priority)
  {
    case Priority::HIGH:
    {
      high_.push_back(element);
      break;
    }

    case Priority::NORMAL:
    {
      normal_.push_back(element);
      break;
    }

    case Priority::LOW:
    {
      low_.push_back(element);
      break;
    }
  }
}

template <typename T>
T PriorityQueue<T>::get()
{
  if (isEmpty())
  {
    throw std::invalid_argument("List is empty");
  }

  if (!high_.empty())
  {
    const T tmp = high_.front();
    high_.pop_front();
    return tmp;
  }

  if (!normal_.empty())
  {
    const T tmp = normal_.front();
    normal_.pop_front();
    return tmp;
  }
  else
  {
    const T tmp = low_.front();
    low_.pop_front();
    return tmp;
  }
}

template <typename T>
void PriorityQueue<T>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
  return high_.empty() && normal_.empty() && low_.empty();
}

#endif
