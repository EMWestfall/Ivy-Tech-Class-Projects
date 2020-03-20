'''
Author:     Eric Westfall
Date:       5/1/2018
File:       apiPull.py
Purpose:    Pull apis and write to a file.
'''

import urllib.request as req

outfile = open("apiFile.txt", "w")
coinJSON = req.urlopen("https://api.coinmarketcap.com/v2/ticker/")
outfile.write(coinJSON.read().decode())
outfile.close()
