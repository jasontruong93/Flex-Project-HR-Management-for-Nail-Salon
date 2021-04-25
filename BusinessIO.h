#ifndef BUSINESSIO_H
#define BUSINESSIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class BusinessIO {
private:
	std::string file_name;
	std::fstream file;
public:

	BusinessIO(std::string file_name);
	bool open(std::ios_base::openmode openMode);	
	void close();	
	void readAll(std::vector<std::string>& records);
	bool addRecord(std::vector<std::string> record); //add new record (add more information to the file)
	bool removeRecord(const std::string& id); // remove record 
	
	void updateRecord(std::string id, const std::string& newRecordInfo, const bool& isAddNew = false); //modify record

	bool isExistRecord(const std::string &id, const std::vector<std::string> &listRecord, int &indexRecord);
	bool isOpen(std::string file_name);
};
#endif // !BUSINESSIO_H
