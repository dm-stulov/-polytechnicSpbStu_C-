#ifndef LAB6_FUNC_HPP
#define LAB6_FUNC_HPP


class func {
public:
  void operator()(long long int value);

  long long int returnMin() const;

  long long int returnMax() const;

  long double returnMean() const;

  long long int returnPositive() const;

  long long int returnNegative() const;

  long long int returnEvenSum() const;

  long long int returnOddSum() const;

  long long int returnCount() const;

  bool comparatorFirstLast() const;

private:
  long long int maximum;
  long long int minimum;
  long long int count;
  long long int positive;
  long long int negative;
  long long int odd_sum;
  long long int even_sum;
  long long int first;
  long long int last;
};


#endif
