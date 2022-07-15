#ifndef IDEXCEPTION_H
#define IDEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class IllegalIDException:exception{
private:
	string msg;
public:
	IllegalIDException():msg{"IllegalIDException"}{}
	IllegalIDException(string_view s):msg{s}{}
	virtual ~IllegalIDException()=default;
	virtual const char* what() const noexcept override{
		return msg.c_str();
	}
};
#endif