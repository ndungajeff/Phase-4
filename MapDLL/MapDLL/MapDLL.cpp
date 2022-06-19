// Author: Jeff Ngeama
// Course: CIS 687
//Syracuse University
//Project 2
//Start Date: 04/22/22
//Last Updated Date: 06/19/22

#include "pch.h"
#include <utility>
#include <limits.h>
#include "MapDLL.h"
#include "Map.h"

// define the map function with the input parameters
//input:input file directory name,output file directory name,intermediate output directory name
//     :input filename,output filename,intermediate file name
//     :intermediate file name as key
//     :paragragh to be tokenized as value
// output: msg if map function run to completion
string map(string _infiledirectory, string _outfiledirectory, string _intermediatefiledirectory,
	string _infilename, string _outfilename, string _intermediatefilename, string key, string value)
{ 
	//set up the output to show "map completed"
	string mapmapresult = "map completed";
	//create an object of the map class
	Map mapobj(_infiledirectory, _outfiledirectory, _intermediatefiledirectory, _infilename, _outfilename, _intermediatefilename);
	//call the map function
	mapobj.map(key, value);
	// return the output msg
	return mapmapresult;

}