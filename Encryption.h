#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
private:
	const static char key = 'K';
public:
	static std::string encryptDecrypt(const std::string& inputStr);
};

#endif // !ENCRYPTION_H


