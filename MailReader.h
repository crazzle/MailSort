/*
 * MailHandler.h
 *
 *  Created on: 11.03.2011
 *      Author: mark
 */

#ifndef MAILHANDLER_H_
#define MAILHANDLER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>

class MailReader {
public:
	MailReader();
	virtual ~MailReader();
	std::string readMailFileIn(const char *mailFile) const;
};

#endif /* MAILHANDLER_H_ */
