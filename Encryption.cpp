//Implementation file of Encryption.h

#include "Encryption.h"

//function to encrypt decrypt the string input
//Method: Simple XOR Encryption/Decryption
//Source: https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp?fbclid=IwAR1WHpOm8xIIo8ggApzZ0tyhySGP1-EpehapE-ADcTVGbIGg9Pvq-SzruBE

std::string Encryption::encryptDecrypt(const std::string& inputStr) {
	std::string output = inputStr;
	for (unsigned i = 0; i < inputStr.size(); ++i) {
		if (inputStr[i] != '\n') {
			output[i] = inputStr[i] ^ key;
		}
		else {
			output[i] = inputStr[i];
		}
	}
	return output;
}