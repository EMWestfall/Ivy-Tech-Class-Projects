/*
Author:		Eric Westfall
Date:		5/11/2018
File:		crytpoAnalyzer.cpp / crytpoAnalyzer.dll
Purpose:	Performs cryptocurrency analysis after being called from a Python script.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include "cryptoAnalyzer.h"

using namespace std;

//PyMODINIT_FUNC PyInit_cryptoAnalyzer();

//This is the main function called by Python. It calls the function to read apiFile.txt
//and then the function that writes to coinFlatFile.txt.
int main() {
	string apiString;
	string timestamp = "";
	//Reads the API file and stores it into vector coins
	vector<coinMarketCap>(coins) = readFileFunctions::parseFile("apiFile.txt");
	//Open file for reading
	ifstream apiFile("apiFile.txt");
	apiFile.close();
	writeFileFunctions::writeToFile(coins, "12349");
	for (coinMarketCap coin : coins) {
		cout << coin.toString() << endl;
	}
	cout << "<Enter> to exit";
	cin.ignore();
	cin.get();
	return 0;
}

/*
static PyMethodDef cryptoAnalyzer_methods[] = {
	// The first property is the name exposed to Python, the second is the C++
	// function name that contains the implementation.
	{ "analyzeCrypto", (PyCFunction)analyzeCrypto, METH_O, nullptr },

	// Terminate the array with an object containing nulls.
	{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef cryptoAnalyzer_module = {
	PyModuleDef_HEAD_INIT,
	"cryptoAnalyzer",                        // Module name to use with Python import statements
	"Provides analysis functions on cryptocurrency web API data.",  // Module description
	0,
	cryptoAnalyzer_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_cryptoAnalyzer() {
	return PyModule_Create(&cryptoAnalyzer_module);
}
*/