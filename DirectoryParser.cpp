/*
 * DirectoryParser.cpp
 *
 *  Created on: 11.03.2011
 *      Author: mark
 */

#include "DirectoryParser.h"

using namespace std;


DirectoryParser::DirectoryParser(const string& initDir){
	// TODO Auto-generated constructor stub
	_folder = 0x4;
	_initDir = initDir;

	#ifdef WIN32
		_hFile = _findfirst((initDir+std::string("*.*")).c_str(), &_fileinfo);
	#else
		_dirStream = opendir(initDir.c_str());
	#endif
}

DirectoryParser::~DirectoryParser() {
	// TODO Auto-generated destructor stub
}

/*
 * Parse directory and return true if there is a file,
 * write filename into "file" and filetype into "type"
 */
bool DirectoryParser::getNextFile(string& file, string& type){
#ifdef WIN32
	if (hFile != -1L){
		if(_findnext(hFile, &fileinfo) == 0 );
		{
			string filename = fileinfo.name;
			if((filename.compare(".") != 0) && (filename.compare("..") != 0)){
				if((fileinfo.attrib & _A_SUBDIR) == 0){
					if(filename.size() > 4){
						if(filename.substr(filename.size()-4,4).compare(".eml") == 0){
							file = filename;
							type = "FILE";
							return true;
						}
					}
				}
				else{
					file = filename;
					type = "FOLDER";
					return true;
				}
			}
			type = "NULL";
			file = "NULL";
			return true;
		}
	}
#else
	if(_dirStream != NULL){
		if((_strDir = readdir(_dirStream))){
			string filename = string(_strDir->d_name);
			if((filename.compare(".") != 0) && (filename.compare("..") != 0)){
				if(_strDir->d_type != _folder){
					if(filename.size() > 4){
						if(filename.substr(filename.size()-4,4).compare(".eml") == 0){
							file = filename;
							type = "FILE";
							return true;
						}
					}
				}
				else{
					type = "FOLDER";
					file = filename;
					return true;
				}
			}
			file = "NULL";
			type = "NULL";
			return true;

		}
		closedir(_dirStream);
	}
#endif
	else{
		cout << "Could not open stream" << endl;
	}
	file = "NULL";
	type = "NULL";
	return false;
}

