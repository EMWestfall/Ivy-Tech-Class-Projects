#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "cryptoAnalyzer.h"

//Functions in this namespace trim whitespace from strings
//These functions are only used in this file
namespace trim {

	// trim from start
	static inline std::string &ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	static inline std::string &rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	static inline std::string &trim(std::string &s) {
		return ltrim(rtrim(s));
	}
}

using namespace std;

//readFileFunctions namespace

//Returns bool if the entered symbol is a coin of interest as defined above
bool readFileFunctions::isCoinOfInterest(string symbol) {
	for (string quotesAdded : coinsOfInterest) {
		quotesAdded = "\"" + quotesAdded + "\"";
		if (quotesAdded == symbol) {
			return true;
		}
	}
	return false;
}
//Main function of readFileFunctions namespace that reads the file and outputs
//a vector of CoinCurrent class instances
vector<coinMarketCap> readFileFunctions::parseFile(string fileName) {
	ifstream inFile(fileName);
	string line, name[2], symbol[2], price[2], volume[2], change1h[2], change24h[2], change7d[2];
	bool isOfInterest;
	int switchVar;
	int count = 0; //tracks the coins retrieved count
	vector<coinMarketCap>coins;
	while (getline(inFile, line)) {
		if (line.find("}") != string::npos) { //resets isOfInterest when a right brace is found
			isOfInterest = false;
			cout << "reset brace" << endl;
		}
		int i = 0;
		while ((isCoinOfInterest(line.substr(i, 5)) == false) && (line.substr(i, 5).size() == 5)) { //checks for coin of interest
			++i;
			isOfInterest = isCoinOfInterest(line.substr(i, 5)); //sets isOfInterest to true when a coin of interest is found
		}
		if (isOfInterest == true) { //continues searching for a coin of interest if this statement is false
			cout << "coin of interest found, loading conditional" << endl;
			string header = getHeader(line);
			cout << "header = " << header << endl;
			if (header == "") { //continues to the next iteration if a header of interest isn't found
				continue;
			}
			line = stripLine(line); //strips the line down to its data
			cout << "data = " << line << endl;
			switchVar = findType(header);
			cout << "switchVar = " << switchVar << endl;
			switch (switchVar) { //stores the data in the appropriate variable
			case 0: symbol[0] = header; symbol[1] = line; name[0] = "\"name\""; name[1] = matchName(header); //matches the name with the symbol
			case 1: price[0] = header; price[1] = line;
			case 2: volume[0] = header; volume[1] = line;
			case 3: change1h[0] = header; change1h[1] = line;
			case 4: change24h[0] = header; change24h[1] = line;
			case 5: change7d[0] = header; change7d[1] = line;
			}
			//creates a new class instance when all the info is gathered
			if (change7d[0] != "") {
				coinMarketCap newCoin(name[1], symbol[1], stof(price[1]), stof(volume[1]),
					stof(change1h[1]), stof(change24h[1]), stof(change7d[1]));
				coins.push_back(newCoin);
				//reset the variables
				for (int i = 0; i < 2; i++) {
					name[i] = "";
					symbol[i] = "";
					price[i] = "";
					volume[i] = "";
					change1h[i] = "";
					change24h[i] = "";
					change7d[i] = "";
				}
				count++;
			}
		}
	}
	return coins;
}
string readFileFunctions::matchName(string header) {
	try {
		if (header == "BTC") {
			return "Bitcoin";
		}
		else if (header == "ETH") {
			return "Ethereum";
		}
		else if (header == "XRP") {
			return "Ripple";
		}
		else if (header == "BCH") {
			return "Bitcoin Cash";
		}
		else if (header == "EOS") {
			return "EOS";
		}
		else if (header == "LTC") {
			return "Litecoin";
		}
		else if (header == "ADA") {
			return "Cardano";
		}
		else if (header == "XLM") {
			return "Stellar";
		}
		else if (header == "TRX") {
			return "TRON";
		}
		else if (header == "ZEC") {
			return "Zcash";
		}
		else {
			throw("");
		}
	}
	catch (...) {
		cout << "Error getting coin name with symbol input." << endl;
	}
}

int readFileFunctions::findType(string header) {
	if (header == "\"symbol\"") {
		return 0;
	}
	else if (header == "\"price\"") {
		return 1;
	}
	else if (header == "\"volume_24h\"") {
		return 2;
	}
	else if (header == "\"percent_change_1h\"") {
		return 3;
	}
	else if (header == "\"percent_change_24h\"") {
		return 4;
	}
	else if (header == "\"percent_change_7d\"") {
		return 5;
	}
}
string readFileFunctions::getHeader(string line) {
	for (int i = 0; i < 6; i++) {
		string header;
		switch (i) {
		case 0:
			header = "\"symbol\"";
		case 1:
			header = "\"price\"";
		case 2:
			header = "\"volume_24h\"";
		case 3:
			header = "\"percent_change_1h\"";
		case 4:
			header = "\"percent_change_24h\"";
		case 5:
			header = "\"percent_change_7d\"";
		}
		if (line.find(header) != string::npos) {
			return header;
		}
	}
	return "failed";
}
string readFileFunctions::stripLine(string line) {
	for (int i = 0; i < 6; i++) {
		string header;
		switch (i) {
		case 0:
			header = "\"symbol\"";
		case 1:
			header = "\"price\"";
		case 2:
			header = "\"volume_24h\"";
		case 3:
			header = "\"percent_change_1h\"";
		case 4:
			header = "\"percent_change_24h\"";
		case 5:
			header = "\"percent_change_7d\"";
		}
		int startPositionToErase = line.find(header);
		line = line.erase(startPositionToErase, header.size()+1);
	}
	return trim::trim(line);	
}

//writeFileFunctions namespace

void writeFileFunctions::writeToFile(vector<coinMarketCap>(coins), string timestamp) {
	string timeS = "Timestamp: " + timestamp + "\n";
	for (coinMarketCap coin : coins) { //write files
		try {
			if (coin.getSymbol() == "\"BTC\"") {
				ofstream outputFile("BTC.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"ETH\"") {
				ofstream outputFile("ETH.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"XRP\"") {
				ofstream outputFile("XRP.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"BCH\"") {
				ofstream outputFile("BCH.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"EOS\"") {
				ofstream outputFile("EOS.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"ADA\"") {
				ofstream outputFile("ADA.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"LTC\"") {
				ofstream outputFile("LTC.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"XLM\"") {
				ofstream outputFile("XLM.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"TRX\"") {
				ofstream outputFile("TRX.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else if (coin.getSymbol() == "\"ZEC\"") {
				ofstream outputFile("ZEC.txt");
				outputFile.seekp(-2, ios::end);
				outputFile.write(timeS.c_str(), timeS.size());
				outputFile.write(coin.writeFile().c_str(), coin.writeFile().size());
				outputFile.close();
			}
			else {
				throw("");
			}
		}
		catch (...) {
			ofstream outputFile("errorLog.txt");
			outputFile.seekp(0, ios::end);
			string cstring = "\nInvalid coin when trying to write coin data to file.\n";
			outputFile.write(timeS.c_str(), timeS.size());
			outputFile.write(cstring.c_str(), cstring.size());
		}
	}
}