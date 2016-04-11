/*
 * MailWriter.cpp
 *
 *  Created on: 13.03.2011
 *      Author: mark
 */

#include "MailWriter.h"

#ifdef CbWIN32
#include <windows.h>
#endif

using namespace std;

MailWriter::MailWriter() {
	// TODO Auto-generated constructor stub

}

MailWriter::~MailWriter() {
	// TODO Auto-generated destructor stub
}

/*
 * Write Mail into its folder
 */
const char* MailWriter::writeMailFileTo(const char* folderFile, string mailFile) const{
	ofstream mailOut(folderFile, ios::binary);
	if(!mailOut){
		cout << "failed to open outputstream";
		return "NOOPEN";
	}

	mailOut << mailFile;
	mailOut.close();
	return "VALID";
}

/*
 * Just to create a folder...
 */
void MailWriter::createFolder(const char *folder) const{
#ifdef CbWIN32
	::CreateDirectory(folder, 0);
#else 
	mkdir(folder, 0777);
#endif
}


/*
 * Copies files at a specified location to another location
 */
void MailWriter::copyFile(const string& input, const string& output) const{
	/*
	 * Outputstream
	 */
	ofstream mailOut(output.c_str(), ios::binary);
	if(!mailOut){
		cout << "failed to open outputstream";
	}

	/*
	 * Inputstream
	 */
	ifstream mailIn(input.c_str(), ios::binary);
	if(!mailIn){
		cout << "failed to open inputstream";
	}

	/*
	 * read from instream and write file into outstream
	 */
	string file;
	getline(mailIn, file, '\x00');
	mailOut << file;

	/*
	 * Close streams
	 */
	mailOut.close();
	mailIn.close();
}
