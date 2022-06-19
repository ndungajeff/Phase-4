// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 2
//Start Date: 04/22/22
//Last Updated Date: 05/12/22

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "pch.h"

using namespace std;
// file manageger class to handle all file operations
class FileManager
{
private:
	//name of the directory
	string directoryname;
	//name f the file name
	string fileName;
	// the mode,if mode = a then output will be appedned to the file
	//if mode = r ,the file will be open for reading
	//if mode = w ,the file will be open for writing
	char mode;

public:
	fstream currentFile;
	//vector to hold all tokonized words
	vector<string> fileContent;
	// constructor to create fstream file object and initialize directory file name and the mode
	FileManager(string _directorytype, string _filename, char _mode);
	//method to open file for reading
	void readFile();
	// read the contents of the file
	string readFileContentLine(size_t l);
	//method to close the input file 
	string closeinfile();
	//method to close the output file
	string closeoutfile();
	//write the input string to the output file
	string writetoFile(string);
	//append the input string to the output file
	string appendtofile(string);

	//getters
	string getDirectoryName();
	string getFileName();
	char   getMode();

	// Setters
	void setDirectoryName(string);
	void setFileName(string);
	void setMode(char);
	// open files for reading,writing and appending
	void openfileforreading();
	// open files for writing
	void openfileforwriting();
	// open files for  appending
	void openfileforappending();

};
// constructor ,initialize the directory name and file name
FileManager::FileManager(string _directoryname, string _filename, char _mode)
{
	directoryname = _directoryname;
	fileName = _filename;
	mode = _mode;
}
// open the file for reading
void FileManager::openfileforreading()
{
	if (mode == 'r')
	{
		currentFile.open(directoryname + '\\' + fileName, std::fstream::in);
	}

}
//open the file for wrting
void FileManager::openfileforwriting()
{

	if (mode == 'w')
	{
		currentFile.open(directoryname + '\\' + fileName, std::fstream::out);
	}
}
//open file for appending
void FileManager::openfileforappending()
{
	if (mode == 'a')
	{
		currentFile.open(directoryname + '\\' + fileName, std::fstream::app);
	}
}


//read a line from a file
void FileManager::readFile()
{
	if (currentFile.is_open()) {
		string input;
		// read line by line from the file and save the contents in the vector
		for (int i = 0; getline(currentFile, input); i++) {
			fileContent.push_back(input);
		}
	}

	closeinfile();
}
string FileManager::readFileContentLine(size_t l) {
	/*
	This function can be called in main() once the file has been read with
	readFile(). This function returns the contents of the file
	at line l.
	*/

	if (l > fileContent.size()) {
		throw invalid_argument("Line number out of bounds.");
	}
	return fileContent[l];
}


// close the outfile
string FileManager::closeoutfile()
{
	if (currentFile.is_open()) {
		currentFile.close();
	}
	else { return "Error"; }
	return "Success";
}

//close the infile
string FileManager::closeinfile()
{
	if (currentFile.is_open()) {
		currentFile.close();
	}
	else { return "Error"; }
	return "Success";
}


//write line  to the output file
string FileManager::writetoFile(string dataline)
{
	if (currentFile.is_open()) {
		currentFile << dataline + "\n";
		currentFile.flush();
		closeoutfile();
		return "Success";
	}
	else {
		return "Error";
	}


}
// append a line to the intermediate file
string FileManager::appendtofile(string dataline)
{
	if (currentFile.is_open()) 
	{	
		currentFile << dataline;	
		currentFile.flush();
		closeoutfile();
		return "Success";
	}
	else {
		return "Error";
	}

}


// get the file directory name
string FileManager::getDirectoryName()
{
	return directoryname;
}
//get file name
string FileManager::getFileName()
{
	return fileName;
}

char   FileManager::getMode()
{
	return mode;
}


//setters
void FileManager::setDirectoryName(string _directoryname)
{
	directoryname = _directoryname;
}

void FileManager::setFileName(string _filename)
{
	fileName = _filename;
}

void FileManager::setMode(char _mode)
{
	mode = _mode;
}

#endif
