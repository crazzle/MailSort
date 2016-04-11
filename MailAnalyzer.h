/*
 * MailAnalyzer.h
 *
 *  Created on: 12.03.2011
 *      Author: mark
 */

#ifndef MAILANALYZER_H_
#define MAILANALYZER_H_

#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cctype>
#include <algorithm>



class MailAnalyzer {
public:
	MailAnalyzer();
	virtual ~MailAnalyzer();

	const std::string analyzeMailHeaderOnDate(std::string content, int idx);

	std::vector<std::string>* tokenize(std::string content, std::string delimiter);

	const std::string getReceiveDate(std::string recToken);

	std::vector<std::string>* stripVectorElements(std::vector<std::string> *vec);

	const void stripString(std::string *str) const;

	const std::string formatDate(std::vector<std::string> *dateElements) const;

	const std::string toMonthNumber(const std::string& month) const;

};

#endif /* MAILANALYZER_H_ */
