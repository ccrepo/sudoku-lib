#ifndef SUDOKU_AUTOSET_H
#define SUDOKU_AUTOSET_H

#include "sudoku_atomic_flag.h"

namespace cc {
namespace tools {
namespace sudoku {

template<typename T>
class Autoset final {

	using value_type [[maybe_unused]] =
			typename std::enable_if<

  (std::is_same<AtomicFlagSeqCst, T>::value) ||

  (std::is_same<AtomicFlagRelAcq, T>::value) ||

  (std::is_same<AtomicFlagSemiRelaxed, T>::value) ||

  (std::is_same<int64_t, T>::value) ||

  (std::is_same<int32_t, T>::value) ||

  (std::is_same<int16_t, T>::value) ||

  (std::is_same<bool, T>::value)>::type;

};

//

template<typename T>
class AutosetI {

public:
  AutosetI(std::atomic<T>& variable, const T& value) :
    _variable(variable), _value(value) {
  }

private:
  ~AutosetI() {
    _variable = _value;
  }

  friend class Autoset<bool>;
  friend class Autoset<int16_t>;
  friend class Autoset<int32_t>;
  friend class Autoset<int64_t>;

private:
  std::atomic<T>& _variable;

  const T _value;

private:
  AutosetI(const AutosetI&) = delete;
  AutosetI& operator=(const AutosetI&) = delete;
};

template<typename T>
class AutosetF {

public:
  AutosetF(T& variable) :
    _variable(variable) {
  }

private:
  ~AutosetF() {
    _variable.set();
  }

  friend class Autoset<AtomicFlagSeqCst>;
  friend class Autoset<AtomicFlagRelAcq>;
  friend class Autoset<AtomicFlagSemiRelaxed>;

private:
  T& _variable;

private:
  AutosetF(const AutosetF&) = delete;
  AutosetF& operator=(const AutosetF&) = delete;
};

//

template<>
class Autoset<bool> : public AutosetI<bool> {
public:
  Autoset(std::atomic<bool>& variable, const bool& value) :
    AutosetI(variable, value) {
  }
};

template<>
class Autoset<int16_t> : public AutosetI<int16_t> {
public:
  Autoset(std::atomic<int16_t>& variable, const int16_t& value) :
    AutosetI(variable, value) {
  }
};

template<>
class Autoset<int32_t> : public AutosetI<int32_t> {
public:
  Autoset(std::atomic<int32_t>& variable, const int32_t& value) :
    AutosetI(variable, value) {
  }
};

template<>
class Autoset<int64_t> : public AutosetI<int64_t> {
public:
  Autoset(std::atomic<int64_t>& variable, const int64_t& value) :
    AutosetI(variable, value) {
  }
};

//

template<>
class Autoset<AtomicFlagRelAcq> : public AutosetF<AtomicFlagRelAcq> {
public:
  Autoset(AtomicFlagRelAcq& variable) :
    AutosetF(variable) {
  }
};

template<>
class Autoset<AtomicFlagSeqCst> : public AutosetF<AtomicFlagSeqCst> {
public:
  Autoset(AtomicFlagSeqCst& variable) :
    AutosetF(variable) {
  }
};

template<>
class Autoset<AtomicFlagSemiRelaxed> : public AutosetF<AtomicFlagSemiRelaxed> {
public:
  Autoset(AtomicFlagSemiRelaxed& variable) :
    AutosetF(variable) {
  }
};

}
}
}

#endif
