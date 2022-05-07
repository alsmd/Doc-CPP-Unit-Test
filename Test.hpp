#pragma once
#include <string>
#include <iostream>

namespace doc{

namespace Color {
	static char const *red = "\033[0;31m";
	static char const *green = "\033[0;32m";
	static char const *yellow = "\033[0;33m";
	static char const *blue = "\033[0;34m";
	static char const *purple = "\033[0;35m";
	static char const *cyan = "\033[0;36m";
	static char const *white = "\033[0;37m";
};

class Test
{
private:
	std::string	_name;
public:
	Test(/* args */){

	}
	~Test(){
		
	}
	Test *title(std::string str){
		std::cout << Color::yellow << str << std::endl;
		return this;
	}

	Test *name(std::string str){
		this->_name = str;
		// this->_name.append(str); 
		// this->_name.append(Color::white);
		return this;
	}
	
	template<typename type1, typename type2>
	void assertEqual(type1 value1, type2 value2){
		if (value1 == value2){
			std::cout << Color::green << this->_name << "\n" << Color::white;
			// std::cout << "" << this->_name << ": "<< Color::green  <<  "\n\t\tOK! " << value1 << " equals to " << value2 <<"\n" << Color::white;
		}else{
			std::cout << Color::red << this->_name << ": "  << Color::red << "\n\t\tKO! expected " << value1 << " to be " << value2 << "\n" << Color::white;
		}
	}
};

}

//test->name("passando valores diferentes tem que dar 0")->assert()

