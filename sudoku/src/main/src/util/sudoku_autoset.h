#ifndef SUDOKU_AUTOSET_H
#define SUDOKU_AUTOSET_H

#include <atomic>

namespace cc {
namespace tools {
namespace sudoku {

template<typename T, typename U>
class Autoset final {

	using value_type [[maybe_unused]] =
			typename std::enable_if<

  (std::is_same<int64_t, U>::value &&
      std::is_same<std::atomic<int64_t>, T>::value) ||

  (std::is_same<int32_t, U>::value &&
      std::is_same<std::atomic<int32_t>, T>::value) ||

  (std::is_same<int16_t, U>::value &&
      std::is_same<std::atomic<int16_t>, T>::value) ||

  (std::is_same<bool,    U>::value &&
      std::is_same<std::atomic<bool>, T>::value)>::type;

public:
	explicit Autoset(T& variable, const U& value) :
	_variable(variable), _value(value) {
	}

	virtual ~Autoset() {
	  _variable.store(_value);
	}

private:
	T& _variable;

	const T _value;

private:
	Autoset(const Autoset&) = delete;
	Autoset& operator=(const Autoset&) = delete;

};

}
}
}

#endif
