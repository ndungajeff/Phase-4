// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 4
//Start Date: 05/22/22
//Last Updated Date: 06/19/22
#include <iostream>
#include <windows.h>
#include <string>
#include <filesystem>
#include <codecvt>
#include <vector>
#include <fstream>
#include <thread>




using namespace std;



typedef string (*funcmap)(string,string,string,string,string,string,string,string);
string getfilecontents(string directoryname, string filename);

int main()
{
	HINSTANCE hDLL;
	funcmap map;
	funcmap map_export;
	const wchar_t* libName = L"MapDLL";

	std::vector<string> filenames0;
	//load the library and assign the handler for the handle to hDLL
	hDLL = LoadLibraryEx(libName, NULL, NULL);   // Handle to DLL
	// proceed only if the handler to hDLL is not NULL
	if (hDLL != NULL) {
		map = (funcmap)GetProcAddress(hDLL, "map");
		if (map != NULL) {
			// define the three directories
			string _infiledirectory = "C:\\Users\\ndung\\source\\repos\\MapDLL\\Input_files";
			string _outfiledirectory = "C:\\Users\\ndung\\source\\repos\\MapDLL\\Output_files";
			string _intermediatefiledirectory = "C:\\Users\\ndung\\source\\repos\\MapDLL\\Intermediate_files";
			//define the 3 file names
			string _infilename = "infilename1.txt";
			string _outfilename = "outfilename1.txt";
			string _intermediatefilename = "intermediatefilename1.txt";
			// the key is name of the intermediate file 
			string key = _intermediatefilename;
			//the value is the sentence we are tokenizing
			//add the file names to filename vector
			filenames0.push_back("inputfile.txt");
			filenames0.push_back("inputfile1.txt");
			filenames0.push_back("inputfile2.txt");
			filenames0.push_back("inputfile3.txt");
			filenames0.push_back("inputfile4.txt");
			//get the number of files in the vector
			int numfiles = filenames0.size();
			//process all the files in the vector
			for (int i = 0; i < numfiles; i = i + 2)
			{
				if ((i + 1) < numfiles)
				{
					//process two files at a time
					string file_name = filenames0[i];
					//use two threads
					//read the contents of the file and pass it to the map function using a new thread
					string contents = getfilecontents(_infiledirectory, file_name);
					std::thread thread1(map, _infiledirectory, _outfiledirectory, _intermediatefiledirectory, file_name,
						_outfilename, _intermediatefilename, key, contents);
					// create the next file name
					string file_name2 = filenames0[i + 1];
					//read the contents of the file and pass it to the map function using a new thread
					string contents2 = getfilecontents(_infiledirectory, file_name2);
					std::thread thread2(map, _infiledirectory, _outfiledirectory, _intermediatefiledirectory, file_name2,
						_outfilename, _intermediatefilename, key, contents2);
					//main thread now will wait until thread 1 finishes
					thread1.join();
					//main thread now will wait until thread 2 finishes
					thread2.join();
				}
				else
				{
					//if the last file is the only one remaining,we only have to process one more file
					// get the last file name to process
					string file_name3 = filenames0[i];
					//read the contents of the file
					string contents3 = getfilecontents(_infiledirectory, file_name3);
					//read the contents of the file and pass it to the map function using a new thread
					std::thread thread3(map, _infiledirectory, _outfiledirectory, _intermediatefiledirectory, file_name3,
						_outfilename, _intermediatefilename, key, contents3);
					// main function now waits until thread finishes the job
					thread3.join();
				}
				
			}

		}
		else
		{
			// if the loading of map function was not successful then write the error msg to the screen
			cout << "Did not load map function correctly." << endl;
		}
		//free the handler to the library
		FreeLibrary(hDLL);
	}
	else {
		// if the DLL library did not load successfully print the error msg
		cout << "Library load failed!" << endl;
	}

	//std::cin.get();
	return 0;
}

string getfilecontents(string directoryname ,string filename)
{
	//create ifstream variable
	ifstream filenm;
	//open the file for reading
	filenm.open(directoryname + '\\' + filename);
	// if the file is not open,terminate and return
	if (!filenm.is_open())
	{
		return "";
	}
	string contents = "";
	string line = "";
	//read a new line from the file
	while (filenm >> line)
	{
		// check if there is a comma in the line
		std::size_t found = line.find('"');
		//if there is a comma delete it and check for more commas
		while (found != std::string::npos)
		{
			line.erase(found, 1);
			found = line.find('"');
		}
		// add the line to the contents variable
		contents = contents + " " + line;
	}
	filenm.close();
	// return the contents
	return contents;
}
