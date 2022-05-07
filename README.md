# C++ Object Unit Test

This is a way to test your functions using a class in a simple way.

## How to install

- git clone https://github.com/alsmd/Doc-CPP-Unit-Test
- cd Doc-CPP-Unit-Test/
- make

it will compile and move the executable to /usr/bin and the header file to /usr/include

## Simple Usage

#

```
//CalculatorTest.hpp
//Our Test Class

#include <Test.hpp>
#include "Calculator.hpp"

class CalculatorTest : doc::Test{
	public:
	CalculatorTest(){}
	~CalculatorTest(){}

	void test_sum(){
		Calculator	calc;
		int			res;

		res = calc.sum(1, 1);
		this->title("Sum");
		this->name("testing sum 1 + 1 equals 2")->assertEqual(res, 2);

		//Forcing error
		res = calc.sum(5, 5);
		this->name("testing sum 5 + 5 equals 9")->assertEqual(res, 9);
	}
};
```

```
//Calculator.hpp

class Calculator{
	public:
	Calculator();
	~Calculator();

	int sum(int a, int b);
};
```

```
//Calculator.cpp
#include "Calculator.hpp"

Calculator::Calculator(){}
Calculator::~Calculator(){}

int Calculator::sum(int a, int b){
	return (a + b);
}

```

```
	doc CalculatorTest.hpp Calculator.cpp
	//first parameter is the file with your tests
	//second and forward opitional parameters is the files where the functions you want to test may be
```

![Results Image](./imgs/testDrive.png)