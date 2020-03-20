#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include "cryptoAnalyzer.h"

using namespace std;

static vector<coinMarketCap>coins;

//CoinCurrent Class
//constructor
CoinCurrent::CoinCurrent(string name, string symbol) {
	this->name = name;
	this->symbol = symbol;
}
string CoinCurrent::getName() {
	return this->name;
}
string CoinCurrent::getSymbol() {
	return this->symbol;
}

//class coinMarketCap

//overloads
ostream& operator<<(ostream& outStream, coinMarketCap& coin) {
	outStream << coin.writeFile();
	return outStream;
}
coinMarketCap::coinMarketCap(string name, string symbol, float price, float volume24h, float change1h,
	float change24h, float change7d) : CoinCurrent(name, symbol) {
	this->price = price;
	this->volume24h = volume24h;
	this->change1h = change1h;
	this->change24h = change24h;
	this->change7d = change7d;
}
//set methods
void coinMarketCap::setCurrentPrice(float price) {
	this->price = price;
}
void coinMarketCap::set24hVolume(float volume) {
	this->volume24h = volume;
}
void coinMarketCap::set1hPrice(float change1h) {
	this->change1h = change1h;
}
void coinMarketCap::set24hPrice(float change24h) {
	this->change24h = change24h;
}
void coinMarketCap::set7dPrice(float change7d) {
	this->change7d = change7d;
}
//get methods
float coinMarketCap::getVolume() {
	return this->volume24h;
}
string coinMarketCap::toString() {
	return this->name + "\nCurrent Price: $" + to_string(this->price) + "\n24h Volume: $" + to_string(this->volume24h)
		+ "\n1h Change: " + to_string(this->get1hChange()) + "%\n24h Change: " + to_string(this->get24hChange())
		+ "%\n7d Change: " + to_string(this->get7dChange()) + "%";
}
string coinMarketCap::writeFile() {
	return "Price: $" + to_string(this->price) + ",\n24h Volume: $" + to_string(this->volume24h)
		+ ",\n1h Change: " + to_string(this->get1hChange()) + "%,\n24h Change: " + to_string(this->get24hChange())
		+ "%,\n7d Change: " + to_string(this->get7dChange()) + "%";
}
float coinMarketCap::get1hChange() {
	return this->change1h;
}
float coinMarketCap::get24hChange() {
	return this->change24h;
}
float coinMarketCap::get7dChange() {
	return this->change7d;
}
float coinMarketCap::getCurrentPrice() {
	return this->price;
}