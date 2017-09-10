/*
 * Main.cpp
 *
 *  Created on: 11.03.2011
 *      Author: mark
 */

#ifdef WIN32
#define FILESLASH	"\\"
#else
#define FILESLASH	"/"
#endif

#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include "MailSorter.h"

using namespace std;

int main(int argc, char **argv){
	/*
	 * parse Arguments
	 */
	string INPUT_DIR;
	string OUTPUT_DIR;
	int IDX = 0;
	bool RECURSIVE = false;
	bool VERBOSE = false;

	for(int i = 1; i < argc; i++){
		if(strcmp(*(argv+i),"-i")==0){
			INPUT_DIR = *(argv+i+1);
		}
		if(strcmp(*(argv+i),"-o")==0){
			OUTPUT_DIR = *(argv+i+1);
		}
		if(strcmp(*(argv+i),"-idx")==0){
			IDX = atoi(*(argv+i+1));
		}
		if(strcmp(*(argv+i),"-v")==0 || strcmp(*(argv+i),"--verbose")==0){
			VERBOSE = true;
		}
		if(strcmp(*(argv+i),"-r")==0 || strcmp(*(argv+i),"-R")==0 || strcmp(*(argv+i),"--Recursive")==0){
			RECURSIVE = true;
		}
	}

	/*
	 * Look if folders are set.
	 */
	if(INPUT_DIR.empty()){
		cout << "No Folder for Input set." << endl << endl;
		exit(1);
	}
	if(OUTPUT_DIR.empty()){
		cout << "No Folder for Output set." << endl << endl;
		exit(1);
	}

	/*
	 * Just to give an overview, use printf when final.
	 */
	cout << "Input Folder: " << INPUT_DIR << "\n";
	cout << "Output Folder: " <<  OUTPUT_DIR << "\n";
	cout << "Header Index: " << IDX << "\n\n";

	/*
	 * look if dir is written right.
	 */
	if(INPUT_DIR.substr(INPUT_DIR.size()-1,1).compare(FILESLASH) != 0){
		INPUT_DIR += FILESLASH;
	}
	if(OUTPUT_DIR.substr(OUTPUT_DIR.size()-1,1).compare(FILESLASH) != 0){
		OUTPUT_DIR += FILESLASH;
	}

	MailSorter ms(INPUT_DIR, OUTPUT_DIR, IDX, VERBOSE, RECURSIVE);
	ms.sortMails();

	cout << "Mailfiles archived." << endl << endl;

	//Keep memory clean
	//delete infiles;

	return 0;
}
