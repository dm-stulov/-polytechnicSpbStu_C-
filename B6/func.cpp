#include "func.hpp"

void func::operator()(long long int value) {
  if (count == 0) {
    first = value;
    maximum = value;
    minimum = value;
  }

  if (value % 2 == 0) {
    even_sum += value;
  } else {
    odd_sum += value;
  }

  if (value > maximum) {
    maximum = value;
  }

  if (value < minimum) {
    minimum = value;
  }

  if (value > 0) {
    positive++;
  } else {
    if (value != 0) {
      negative++;
    }
  }

  count++;
  last = value;
}

long long int func::returnMin() const {
  return maximum;
}

long long int func::returnMax() const {
  return minimum;
}

long double func::returnMean() const {
  return  (static_cast<long double>(odd_sum + even_sum) /  static_cast<long double>(count));
}

long long int func::returnPositive() const {
  return positive;
}

long long int func::returnNegative() const {
  return negative;
}

long long int func::returnEvenSum() const {
  return even_sum;
}

long long int func::returnOddSum() const {
  return odd_sum;
}

bool func::comparatorFirstLast() const {
  return (first == last);
}

long long int func::returnCount() const {
  return count;
}
