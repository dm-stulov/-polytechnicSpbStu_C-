#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <list>
#include <stdexcept>

template <typename T>
class PriorityQueue
{
  public:
    enum class Priority
      {
        LOW,
        NORMAL,
        HIGH
      };

    void add(Priority priority, const T &element);
    T get();
    void accelerate();
    bool isEmpty() const;

  private:
    std::list<T> high_;
    std::list<T> normal_;
    std::list<T> low_;
};

#endif
