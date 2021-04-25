//Implementation file of BusinessIO.h
#include "BusinessIO.h"
#include "Encryption.h"
#include "Utility.h"

//constructor
BusinessIO::BusinessIO(std::string file_name) {
	this->file_name = file_name;
}
//open the file
bool BusinessIO::open(std::ios_base::openmode openMode) {
	//open the file
	file.open(file_name, openMode);

	//if error occurs, display the error
	if (!file) {
		return false;
	}
	return true;
}

//close the file
void BusinessIO::close() {
	file.close();
}


//Read all records from the file, then save to vector records
void BusinessIO::readAll(std::vector<std::string> &records) {

	//Open the file(in read-only mode)
	//if open fails, return
	if (!this->open(std::ios::in)) {
		return;
	}
	//read each line and add it to the vector until end of the file
	std::string line;
	while (getline(file, line)) {
		//decrypt string
		std::string decriptStr = Encryption::encryptDecrypt(line);
		records.push_back(decriptStr);
	}
	//close the file
	this->close();
}

//Add record into the file
//record: a vector stores all items of each line
bool BusinessIO::addRecord(std::vector<std::string> record) {
	//Open the file in Read, Write, Append mode
	//Check the error
	if (!this->open(std::ios::in | std::ios::out | std::ios::app)) {
		return false;
	}

	//write new record into the file
	for (int i = 0; i < record.size(); ++i) {
		//encrypt before save to file
		std::string encryptStr = Encryption::encryptDecrypt(record[i]);
		file << encryptStr;
	}
	//close the file
	this->close();
	return true;
}

//remove an existing record out of the file based on the record's ID
bool BusinessIO::removeRecord(const std::string& id) {

	std::vector<std::string> allRecord;
	int indexFound = 0;
	//read all records first
	readAll(allRecord);
	//now, check if the record exists
	//If so, remove it
	//If not, return false because there is no record to remove
	bool isExist = isExistRecord(id, allRecord, indexFound);

	if (isExist) {
		//call 'erase' function of vector to remove specific item at specific index
		// The 'item' us the record
		//The 'index' is the record ID (start at 0)
		allRecord.erase(allRecord.begin() + indexFound);

		std::ofstream outStream;
		outStream.open(file_name);
		//Write all records to the file in Override mode (except the one just removed)
		for (std::string line : allRecord) {

			//encrypt string to save to file
			std::string encryptStr = Encryption::encryptDecrypt(line);
			outStream << encryptStr << "\n";
		}
		//close file before exit
		outStream.close();
		return true;
	}
	return false;
}

//if found this record, it will update
//if not found and isAddNewIfNotExist = true, it will add this record to file
void BusinessIO::updateRecord(std::string id, const std::string& newRecordInfo, const bool& isAddNewIfNotExist) {

	std::vector<std::string> allRecord;
	//find index of the record
	int indexFound = 0;

	//read all records first
	readAll(allRecord);
	
	//now check if the record exists
	//If so, update it
	bool isExist = isExistRecord(id, allRecord, indexFound);
	if (isExist) {
		//Replace the found record with new content
		allRecord.at(indexFound) = newRecordInfo;

		std::ofstream outStream;
		outStream.open(file_name);

		//Now write all records(including the one just updated) to file
		for (std::string line : allRecord) {
			//encrypt string
			std::string encryptStr = Encryption::encryptDecrypt(line);
			outStream << encryptStr << "\n";
		}
		//close before exit
		outStream.close();
		
	}
	//If the record does not exist, add it as a new one
	else if (isAddNewIfNotExist) {
		//if request add new record if it is not exist
		std::vector<std::string> recordList;
		recordList.push_back(newRecordInfo);
		this->addRecord(recordList);
	}
}

//Check whether a record (with ID) exists in the file
bool BusinessIO::isExistRecord(const std::string &id, const std::vector<std::string> &listRecord, int &indexRecord) {

	std::vector<std::string> listInfo; //vector stores all items of each record

	for (int i = 0; i < listRecord.size(); ++i) {
		
		//Get each line from the file. one by one, start from the 1st line
		std::string line = listRecord.at(i);

		//parse the line based on separator '|' to get all items
		Utility::parse(line, '|', listInfo);

		//Having positive size meaning the record has item -> line not empty
		if (listInfo.size() > 0) {
			
			//if found the record we want to check, store its index and return true
			if(listInfo.at(0) == id){
				indexRecord = i; //First record has index of 0
				return true;
			}
		}
	}
	//if we read all lines, but found no record => the record does not exist in the file
	return false;
}

bool BusinessIO::isOpen(std::string file_name) {
	std::ifstream iFile(file_name);
	//if cannot open the file
	if (!iFile) {
		return false;
	}
	else
		return true;
}