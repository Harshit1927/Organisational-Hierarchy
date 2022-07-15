#ifndef NOTEMPTY_H
#define NOTEMPTY_H

#include <exception>
#include <string>

using namespace std;
class NotEmptyException:exception{
private:
	string msg;
public:
	NotEmptyException():msg{"NotEmptyException"}{}
	NotEmptyException(string_view s):msg{s}{}
	virtual ~NotEmptyException()=default;
	virtual const char* what() const noexcept override{
		return msg.c_str();
	}
};
#endif