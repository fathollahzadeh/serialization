#ifndef SocketException_class
#define SocketException_class

#include <string>
using namespace std;

class SocketException {
public:
	SocketException(string s) : message(s) {};

	~SocketException() {};

	string description() { return message; }

private:

	string message;

};

#endif
