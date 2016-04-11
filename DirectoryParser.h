/*
 * DirectoryParser.h
 *
 *  Created on: 11.03.2011
 *      Author: mark
 */

#ifndef DIRECTORYPARSER_H_
#define DIRECTORYPARSER_H_

#ifdef WIN32
#include <io.h>
#else
#include <dirent.h>
#endif
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>


class DirectoryParser {
public:

	DirectoryParser(const std::string& initDir);
	virtual ~DirectoryParser();

	bool getNextFile(std::string& file, std::string& type);

	unsigned char _folder;
	bool _recursive;
	std::string _initDir;

	//Windows or Linux implementation
	#ifdef WIN32
		long _hFile;
		struct _finddata_t _fileinfo;
	#else
		DIR *_dirStream;
		struct dirent *_strDir;
	#endif
};

#endif /* DIRECTORYPARSER_H_ */
