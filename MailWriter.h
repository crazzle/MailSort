/*
 * MailWriter.h
 *
 *  Created on: 13.03.2011
 *      Author: mark
 */

#ifndef MAILWRITER_H_
#define MAILWRITER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>



class MailWriter {
public:
	MailWriter();
	virtual ~MailWriter();

	const char* writeMailFileTo(const char *folderFile, std::string mailFile) const;
	void createFolder(const char* folder) const;
	void copyFile(const std::string& input, const std::string& output) const;
};

#endif /* MAILWRITER_H_ */
