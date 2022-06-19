// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 2
//Start Date: 04/22/22
//Last Updated Date: 05/12/22

#pragma once
#ifdef MAPDLL_EXPORTS
#define MAPDLL_API __declspec(dllexport)
#else
#define MAPDLL_API __declspec(dllimport)
#endif

#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;
//define the function that will be available in the DLL
//input:input file directory name,output file directory name,intermediate output directory name
//     :input filename,output filename,intermediate file name
//     :intermediate file name as key
//     :paragragh to be tokenized as value
// output: msg if map function run to completion
extern "C" MAPDLL_API string map(string _infiledirectory, string _outfiledirectory, string _intermediatefiledirectory,
	string _infilename, string _outfilename, string _intermediatefilename, string key, string value);
