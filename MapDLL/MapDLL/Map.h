// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 2
//Start Date: 04/22/22
//Last Updated Date: 05/12/22

#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <stdio.h>
#include <string>
#include "FileManager.h"
#include <fstream>
#include "pch.h"

using namespace std;

//This class holds word and value for each occurrence of each word in a given line of data. That is this class can be used to
//tokenize a line of data into words.The punctuations are removed from words and coverted to lower case.
//The words are written into an intermediate file.
// 
//This file contains the definations and the implementations of the map class
//it uses the file manager class for all file access activities

class Map
{
private:
	//These are the private date members of the map class
	string buffer;
	int buffersize;
	string infiledirectory, outfiledirectory, intermediatefiledirectory;
	string infilename, outfilename, intermediatefilename;

public:

	// constructor.
	//This constructor takes all directory names and file names that are necessary for creating
	//objects of file mange class
	Map(string _infiledirectory, string _outfiledirectory, string _intermediatefiledirectory,
		string _infilename, string _outfilename, string _intermediatefilename)
	{
		buffer = "";
		buffersize = 250;
		infiledirectory = _infiledirectory;
		outfiledirectory = _outfiledirectory;
		intermediatefiledirectory = _intermediatefiledirectory;
		infilename = _infilename;
		outfilename = _outfilename;
		intermediatefilename = _intermediatefilename;

	}
	//tokenize the value into words and save them in the intermediate file
	void map(string key, string value);
	//Add the words to the buffer and save them in the intermediate file
	string map_export(string key, string value);
	string getBuffer();
	int getBufferSize();
	//set the buffer to a given value
	void setBuffer(string);
	//set the buffer size to a given value
	void setBufferSize(int);
	// To sort and aggregate the values in the intermediate file
	string exporttherest();



};
void Map::map(string key, string value)
{
	//input key :This is the intermediatefilename
	// value	: This is a word
	//Define all the punctution that are to be removed.
	string punction = "!,.;:'$@*&^()%#~?/[]-";
	//This for loop will go through all the punctuations and remove them
	for (int i = 0; i < punction.length(); i++)
	{
		// get the next punctuation
		string letter = punction.substr(i, 1);
		//check if the punctuation is in the value variable
		std::size_t found = value.find(letter);
		//if it is in the value variable remove it
		while (found != std::string::npos)
		{
			value.replace(found, 1, "");
			found = value.find(letter);
		}
	}
	//covert all the upper case in the value variable to lower case
	for (size_t i = 0; i < value.length(); i++)
	{
		string letter = value.substr(i, 1);
		//check each character in the value variable
		char* ch = &letter[0];
		//If the the character is upper case convert it to lower case.
		if (isupper(*ch))
		{
			string s;
			//covert the string variable to character
			s.push_back(tolower(*ch));
			//covert it to lower case
			value.replace(i, 1, s);
		}
	}
	//tokenize the string variable value
	string word = "";
	// create a string array to hold all the words
	string wordArray[500];
	int j = 0;
	// set the number of words to zero at the begining
	int numWords = 0;
	size_t i = 0;
	string msg = "";
	//use the for for loop to go over the characters of value variable
	for (i = 0; i < value.length(); i++)
	{
		string letter = value.substr(i, 1);
		//if the character is not a space,add it to the word
		if (letter != " ")
		{
			word = word + letter;
		}
		else
		{
			//if the character is a space,separate the word
			if (word.length() > 0)
			{
				wordArray[j] = word;
				// call the export method to add the word to the buffer
				// if the length of the buffer is greater than the buffer size,append the content to the intermediate file
				msg = map_export(key, word);
				word = "";
				j = j + 1;
			}
		}
		//closes the last word
		if (i == value.length() - 1)
		{
			wordArray[j] = word;
			msg = map_export(key, word);
			word = "";
			j = j + 1;
		}
	}
	// set the number of words to numwords.
	numWords = j;
	msg = exporttherest();
}
//This export function buffers the output in memory and periodically writes the data to the disk.
//input: key - name of the intermediate file
//       value - a word
// output: none
string Map::map_export(string key, string value)
{
	FileManager file(intermediatefiledirectory, key, 'a');
	file.openfileforappending();

	//add the value to the buffer
	string line = "(" + value + ",1)\n";
	string msg = "";
	buffer = buffer + line;

	//if the length of the buffer is greater than buffer size,add buffer to the intermediate file
	if (buffer.length() < buffersize)
	{
		msg = file.appendtofile(buffer);
		buffer = "";
	}

	return msg;
}
// get the Buffer value
string Map::getBuffer()
{
	return buffer;
}
//get the Buffersize
int Map::getBufferSize()
{
	return buffersize;
}
// set the Buffer value
void Map::setBuffer(string _buffer)
{
	buffer = _buffer;
}
// set the Buffersize
void Map::setBufferSize(int _buffersize)
{
	buffersize = _buffersize;
}
string Map::exporttherest()
{
	FileManager file(intermediatefiledirectory, intermediatefilename, 'a');
	file.openfileforappending(); /// ofstream ofilehandler = 
	string msg = "";

	// write buffer to the intermediate file
	msg = file.appendtofile(buffer); /// &ofilehandler, 
	buffer = "";
	return msg;
}

#endif // MAP_H
