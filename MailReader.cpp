/*
 * MailHandler.cpp
 *
 *  Created on: 11.03.2011
 *      Author: mark
 */


#include "MailReader.h"

using namespace std;

MailReader::MailReader() {
	// TODO Auto-generated constructor stub
}

MailReader::~MailReader() {
	// TODO Auto-generated destructor stub
}

string MailReader::readMailFileIn(const char* mailFile) const{
	ifstream mailIn(mailFile, ios::binary);
	string content;

	if(!mailIn){
		cout << "failed to open file";
		return "NOOPEN";
	}

	getline(mailIn, content, '\x00');

	//cout << endl << content << endl;
	mailIn.close();

	return content;
}
