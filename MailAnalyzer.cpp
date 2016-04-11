/*
 * MailAnalyzer.cpp
 *
 *  Created on: 12.03.2011
 *      Author: mark
 */

#include "MailAnalyzer.h"
using namespace std;
MailAnalyzer::MailAnalyzer() {
	// TODO Auto-generated constructor stub

}

MailAnalyzer::~MailAnalyzer() {
	// TODO Auto-generated destructor stub

}


const string MailAnalyzer::analyzeMailHeaderOnDate(string content, int idx){
	/*
	 * Cut mail content off
	 */
	transform(content.begin(), content.end(), content.begin(), ::tolower);
	size_t headerLength = content.find("from:");
	string header;

	if(headerLength != string::npos){
		header = content.substr(0,headerLength);
	}
	else{
		header = content;
	}

	/*
	 * Get a vector with "Received-Tokens" from Mail Header
	 */
	vector<std::string> *recFields;
	recFields = tokenize(header, "received:");

	if(recFields == NULL){
		//keep memory clean
		delete recFields;
		return "BADFORMAT";
	}

	/*
	 * Take a look at tokenized fields,
	 * could be different content than received...
	 */
	for(size_t i = 0; i < recFields->size(); i++){
		if(recFields->at(i).find("received:") == string::npos){
			recFields->erase((recFields->begin())+i);
			i--;
		}

	}

	/*
	 * does idx exist?
	 */
	if(((size_t)idx < recFields->size())){
		string date = getReceiveDate(recFields->at(idx));
		if(strcmp(date.c_str(), "NODATE")==0){
			return "NODATE";
		}

		//keep memory clean
		delete recFields;
		return date;
	}

	//keep memory clean
	delete recFields;
	return "NOIDX";

}

/*
* String Tokenizer, tokenizes a string by delimiter
*/
vector<string>* MailAnalyzer::tokenize(string content, const string delimiter){
		size_t first = 0;
		first = content.find(delimiter);

		/*
		 * Look if delimiter does exist in content
		 */
		if(first == string::npos){
			return NULL;
		}

		vector<string> *fields = new vector<string>();

		/*
		 * if delimiter is not at first position
		 */
		if(first != 0){
			fields->push_back(content.substr(0,first));
		}


		/*
		 * Look if there was only one delimiter?
		 */
		size_t next = content.find(delimiter,first+1);
		if(next == string::npos){
			fields->push_back(content.substr(0));
			return fields;
		}

		/*
		 * iterate the rest of the content
		 * to look for delimiter
		 */
		do{
			fields->push_back(content.substr(first,next-first));
			first = next;
			next = content.find(delimiter,first+1);
		}while(next != string::npos);
		fields->push_back(content.substr(first,next-first));

		/*
		 * return pointer to
		 * vector of tokens
		 */
		return fields;
}

/*
 * Function to get the date out of receive block
 */
const string MailAnalyzer::getReceiveDate(string recToken){
	//look if there are fields before the received field
	size_t recWordPos = recToken.find("received:");

	//cut them out!
	if(recWordPos != string::npos && recWordPos != 0){
		recToken = recToken.substr(recWordPos);
	}

	//Position of semicolon
	size_t dateBegin = recToken.find(";");

	//Position of next Headerfield
	size_t diffPart = recToken.find(":",recToken.find(":")+1);

	//Is a date in that received header?
	if(dateBegin == string::npos){
		return "NODATE";

	}
	else{ //if yes, cut this header to make searching shorter
		dateBegin = dateBegin+2;
		recToken = recToken.substr(dateBegin, diffPart);
		dateBegin = 0;
	}


	//Position of colon in received header
	size_t	datePos = recToken.find(",", dateBegin);

	//look for right position (sometimes after colon, sometimes after semicolon)
	if(datePos != string::npos){
		datePos++;
	}
	else{
		datePos = dateBegin;
	}

	//skipping whitespaces and other characters that can't be seen to reach the position of the date
	while(	*(recToken.substr(datePos,1).c_str()) <= 32
			|| *(recToken.substr(datePos,1).c_str()) == 127
			|| *(recToken.substr(datePos,1).c_str()) == 129
			|| *(recToken.substr(datePos,1).c_str()) == 141
			|| *(recToken.substr(datePos,1).c_str()) == 143
			|| *(recToken.substr(datePos,1).c_str()) == 144
			|| *(recToken.substr(datePos,1).c_str()) == 157){
		datePos++;
	}

	//get substring which contains the date
	string date = recToken.substr(datePos);

	//tokenize the date --> there is something wrong...
	vector<string> *dateVector = tokenize(date," ");

	//Working with pointer on given object to strip all element's whitespaces in vector
	stripVectorElements(dateVector);

	//Format date to make it "Output Folder Ready"
	string fdate = formatDate(dateVector);

	//keep memory clean
	delete dateVector;

	return fdate ;
}

/*
 * strip whitespaces at beginning and end out of vector elements
 */
vector<string>* MailAnalyzer::stripVectorElements(vector<string> *vec){
	for(size_t i = 0; i < 3; i++){
		stripString(&(vec->at(i)));
	}
	return vec;
}

/*
 * Strip a string
 */
const void MailAnalyzer::stripString(string *str) const{
	while(*(str->substr(0,1).c_str()) <= 32){
		str->erase(0,1);
	}
	while(*(str->substr(str->size()-1,1).c_str()) <= 32){
		str->erase(str->size()-1);
	}
}

/*
 * format the date to make it "folder-friendly"
 */
const string MailAnalyzer::formatDate(vector<string> *dateElements) const{
	if(dateElements->at(0).size()<2){
		dateElements->at(0).insert(0,"0");
	}
	string fdate = dateElements->at(2)+"_"+toMonthNumber(dateElements->at(1))+"_"+dateElements->at(0);
	return fdate;
}

/*
 * just like a table to look up the
 * right number of the month
 */
const string MailAnalyzer::toMonthNumber(const string& month) const{
	if(month.compare("jan") == 0){
		return "01";
	}
	if(month.compare("feb") == 0){
		return "02";
	}
	if(month.compare("mar") == 0){
		return "03";
	}
	if(month.compare("apr") == 0){
		return "04";
	}
	if(month.compare("may") == 0){
		return "05";
	}
	if(month.compare("jun") == 0){
		return "06";
	}
	if(month.compare("jul") == 0){
		return "07";
	}
	if(month.compare("aug") == 0){
		return "08";
	}
	if(month.compare("sep") == 0){
		return "09";
	}
	if(month.compare("oct") == 0){
		return "10";
		}
	if(month.compare("nov") == 0){
		return "11";
	}
	if(month.compare("dec") == 0){
		return "12";
	}

	return "NO_CORRECT_MONTH";
}
