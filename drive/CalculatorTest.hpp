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