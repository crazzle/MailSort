/*
Verbesserungen/Fixes/Best Practices und alles was mir sonst so aufgefallen ist:
- or und and sind nicht standardkonform (verwende || und &&)
- F�r Filesystem-Funktionalit�t gibt es unter Linux und Windows nur unterschiedliche Funktionen, 
  daher ben�tigt man unterschiedliche Implementierungen daf�r. 
- Um zwischen lokalen und Klassenvariablen zu unterscheiden ist es sinnvoll, den Namen aller Klassenvariablen 
  zB einen _ voranzustellen bzw. anzuh�ngen.
- Auch die Variablennamen in den Prototypen vergeben
  - zB Beim Konstruktor mailFile(string, string); wei� der Anwender nicht, ob der erste Parameter 'root' oder 'name' ist, ohne in den Code zu schauen
- using namespace nur in cpp Dateien verwenden!
- Wenn es entsprechende C++-Header gibt, diese statt die C-Header verwenden 
  - zB <cstring> statt <string.h>
- Bessere Fehlerbehandlung
  - zB mittels Return Codes 
  - niemals exit verwenden!
- Variablen erst anlegen, wenn sie ben�tigt werden
- const verwenden (bei Parameter und Memberfunktionen)
  zB std::string mailFile::getName() const; oder 
     const std::string& mailFile::getName() const;
- Strings als (const)-Referenzen �bergeben
- Konstruktor-Initialisierungslisten verwenden
  zB Konstruktor von mailFile
  mailFile::mailFile(const std::string& Root, const std::string& Name) : root(Root), name(Name)  { }
- Datentype Korrektheit (int, unsigned int, size_t), auch in Hinblick auf 64Bit
  - zB Index immer unsigned int oder noch besser size_t
  - string::size() gibt size_t zur�ck. unsigned int und size_t haben unterschiedliche Gr��en auf 64Bit.
- Besser geeignete Konstrukte verwenden
  - zB statt size()==0 empty()
- Zeichenweise lesen und schreiben ist schlecht f�r die Performance. Auch das EOF-Zeichen geh�rt nicht zur E-Mail
  - Mit std::getline(*mailIn, line, '\x00'); Datei aufeinmal einlesen
  - Einfach mailOut << mailFile; zum Schreiben
- Dateien im Binary-Mode �ffnen zum Lesen und Schreiben (std::ios::binary). Ansonsten k�nnen sich New Lines �ndern!
- Lokale Variablen nicht mit new anlegen, sondern auf den Stack  
- Wieso zB vector<string> *recFields; als Membervariable, wenn sie nur lokal in einer Funktion verwendet wird
- filename.substr(filename.size()-4,4): Crash, wenn Dateiname < 4 Zeichen ist!
- Das Matchen auf "From: " bzw "Received: " funktioniert nicht immer, da Header-Field-Namen case insensitive sind. Nach dem ':' kann auch ein TAB kommen.
  -Man k�nnte ToLower auf den ganzen E-Mail Header anwenden
- Bug in for(unsigned int i = 0; i < recFields->size(); i++){
		    if(recFields->at(i).find("Received: ") == string::npos){
			   recFields->erase((recFields->begin())+i);
  Wenn i gel�scht wird, wird i+1 zu i und dann in der n�chsten Iteration nicht getestet
- Es ist besser, wenn man beim Parsen des Verzeichnisses auf eine Datei trifft, diese direkt zu verarbeiten, statt alle Dateien auf Vorrat zu speichern.
  Denn sonst kann zu Hauptspeicherproblemen kommen, wenn mehrere Millionen Datein in den Verzeichnissen liegen.
  zB folgenden Workflow verwenden:
  
	class DirectoryParser {
	public:
	DirectoryParser(const std::string& initDir, bool recursive);
	virtual ~DirectoryParser();
	bool GetNextFile(std::string& file) const;
	};

	...
	DirectoryParser dirParser(INPUT_DIR, recursive)

	std::string file;

	while(dirParser.GetNextFile(file))
	{
		std::string date_string;
		int ret = GetDateFromFile(file, date_string);

		if (ret == 0)
		{
			const std::string outFile = CreateOutFileName(file, date_string);
			CopyFile(file, outFile);
		}
	}
	....
*/


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
