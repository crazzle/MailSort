/*
 * MailSorter.h
 *
 *  Created on: 15.04.2011
 *      Author: mark
 */

#ifndef MAILSORTER_H_
#define MAILSORTER_H_
#include <iostream>
#include "MailReader.h"
#include "MailAnalyzer.h"
#include "MailWriter.h"
#include "DirectoryParser.h"
#include <cstring>

class MailSorter {
public:
	MailSorter( const std::string& INPUT_DIR, const std::string& OUTPUT_DIR, int IDX, bool VERBOSE, bool RECURSIVE);
	virtual ~MailSorter();

	/*
	 * Read command line arguments
	 * and put them into variables
	 */
	std::string _INPUT_DIR; 		//First arg = input folder
	std::string _OUTPUT_DIR;		//Second arg = output folder
	int  _IDX;						//Third arg = IDX
	bool _VERBOSE;					//Need more informations during runtime?
	bool _RECURSIVE; 				//Traverse folders recursively?

	/*
	 * Got different modules...
	 */
	MailReader _mr;
	MailAnalyzer _ma;
	MailWriter _mw;

	void sortMails(const std::string inputDir);
	void sortMails();
};

#endif /* MAILSORTER_H_ */
