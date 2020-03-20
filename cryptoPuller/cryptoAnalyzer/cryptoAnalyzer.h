#include <string>

using namespace std;

class CoinCurrent {
public:
	//constructors
	CoinCurrent(string, string);
	//get methods
	string getName();
	string getSymbol();
protected:
	string name;
	string symbol;
};

class coinMarketCap : public CoinCurrent {
	//overloads
	friend ostream& operator<<(ostream& outStream, coinMarketCap& coin);
public:
	coinMarketCap(string name, string symbol, float price, float volume24h, float change1h,
		float change24h, float change7d);
	//set methods
	void setCurrentPrice(float price);
	void set24hVolume(float volume);
	void set1hPrice(float change1h);
	void set24hPrice(float change24h);
	void set7dPrice(float change7d);
	//get methods
	float getVolume();
	string toString();
	string writeFile();
	//get methods
	float get1hChange();
	float get24hChange();
	float get7dChange();
	float getCurrentPrice();
private:
	float price;
	float volume24h;
	float change1h;
	float change24h;
	float change7d;
};

namespace readFileFunctions {
	const set<string>(coinsOfInterest) = { "BTC", "ETH", "XRP", "BCH", "EOS",
		"ADA", "LTC", "XLM", "TRX", "ZEC" };
	//Returns bool if the entered symbol is a coin of interest as defined above
	bool isCoinOfInterest(string);
	//Main function that reads the file and outputs a vector of CoinCurrent class instances
	vector<coinMarketCap> parseFile(string);
	string matchName(string header);
	int findType(string header);
	string getHeader(string line);
	string stripLine(string line);
}

namespace writeFileFunctions {
	//Writes coin data to the appropriate file
	void writeToFile(vector<coinMarketCap>, string);
}