/*
 * MailSorter.cpp
 *
 *  Created on: 15.04.2011
 *      Author: mark
 */
#ifdef WIN32
#define FILESLASH	"\\"
#else
#define FILESLASH	"/"
#endif
#include "MailSorter.h"
using namespace std;
MailSorter::MailSorter( const std::string& INPUT_DIR, const std::string& OUTPUT_DIR, int IDX, bool VERBOSE, bool RECURSIVE):
	_INPUT_DIR(INPUT_DIR), _OUTPUT_DIR(OUTPUT_DIR), _IDX(IDX), _VERBOSE(VERBOSE), _RECURSIVE(RECURSIVE){

}

MailSorter::~MailSorter() {
	// TODO Auto-generated destructor stub
}

void MailSorter::sortMails(const string inputDir ){
	/*
	 * Some vars for the loop
	 */
	DirectoryParser dp(inputDir);
	string mailcontent;
	string rec;
	string file;
	string type;
	string fileInput;
	if(_VERBOSE){
		cout << "sorting: " << inputDir << endl;
	}

	while(dp.getNextFile(file, type)){
		/*
		 * if the file is really a file and not a folder
		 */
		if(file.compare("NULL") != 0 && type.compare("FILE") == 0){
			fileInput=(inputDir + file);
			mailcontent = _mr.readMailFileIn(fileInput.c_str());
			if(mailcontent.compare("NOOPEN") == 0){
				continue;
			}
			if(_VERBOSE){
				cout << "INPUT: " << fileInput << endl;
			}

			/*
			 * get date of received block,break if no received block exists
			 */
			rec = _ma.analyzeMailHeaderOnDate(mailcontent, _IDX);
			if(rec.compare("NOIDX")==0 && _VERBOSE){
				cout << "NOIDX" << endl;
				continue;
			}
			else if(rec.compare("NODATE")==0 && _VERBOSE){
				cout << "NODATE" << endl;
			}
			else if(rec.compare("BADFORMAT")==0 && _VERBOSE){
				cout << "BADFORMAT" << endl;
				continue;
			}

			/*
			 * Create output folder
			 */
			_mw.createFolder(_OUTPUT_DIR.c_str());

			/*
			 * create date specific folder in output directory
			 */
			rec = _OUTPUT_DIR + rec +  FILESLASH;
			_mw.createFolder(rec.c_str());

			/*
			 * write file in specific folder
			 */
			rec += file;
			if(_VERBOSE){
				cout << "OUTPUT: " << rec << endl;
				cout << "Copyfile" << endl;
				_mw.copyFile(fileInput,rec);
			}
			else{
				_mw.copyFile(fileInput,rec);
			}
			if(_VERBOSE){
				cout << "WRITTEN: " << rec << endl << endl;
			}
		}
		else if(_RECURSIVE == true && type.compare("FOLDER") == 0){
			/*
			 * create new dirparser with new INPUT DIR,
			 * if file is a folder
			 */
			string f;
			f.append(inputDir);
			f.append(file);
			f.append(FILESLASH);
			sortMails(f.c_str());
		}
	}
}

void MailSorter::sortMails(){
	sortMails(_INPUT_DIR);
}
