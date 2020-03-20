'''
Author:		Eric Westfall
Date:		5/8/2018
File:		Hangman.py
Purpose:	Implement Hangman.
'''
import os
import math
import time
import random as rand
from tkinter import *

#player status
class playerStatus:
    def __init__(self):
        self._strikes = 0 #stores the number of strikes the player has
        self._incorrect = [] #stores the letters the user has gotten incorrect

    def getStrikes(self):
        return self._strikes

    def getIncorrect(self):
        return self._incorrect

    def incorrectString(self):
        string = ""
        for character in self._incorrect:
            string += character
        return string

    def setStrikes(self, strikes):
        self_strikes = strikes

    def incrementStrikes(self):
        self._strikes += 1

    def appendIncorrect(self, character):
        self._incorrect.append(character)

    def lostGame(self): #check if the game is lost
        return self._strikes > 6

#game object
class gameStatus:
    def __init__(self):
        self._word = self.chooseWord() #{letter : bool isLetterGuessed?}

    def getWord(self):
        return self._word

    def getWordString(self): #return the word as a string
        string = ""
        for index in range(len(self._word)):
            string += self.getLetter(index)
        return string

    def getLetter(self, index): #returns dictionary key
        return list(self._word.keys())[index]

    def getGuessedStatus(self, index):
        return self._word[self.getLetter(index)]

    def setGuessedStatus(self, key, status = True):
        self._word[key] = status

    def chooseWord(self): #choose a word from the dictionary file
        dictionary = "dictionary.txt"
        while os.path.isfile(dictionary) == False:
            dictionary = input("File not found, input the dictionary file: ")
        dictionaryFile = open(dictionary, "r")
        dictList = dictionaryFile.readline().split() #split the dictionary file into a list of words
        dictionaryFile.close()
        word = list(dictList[rand.randint(0, 16954)]) #choose a word at random
        dictToReturn = {}
        for letterIndex in range(len(word)): #convert to dictionary and initialize to all false
            dictToReturn[word[letterIndex]] = False
        return dictToReturn

    def getWordLen(self):
        return len(self._word)

    def winnerWinnerChickenDinner(self): #checks if the user has won the game : returns bool, true if game is won
        for letterIndex in range(len(self._word)):
            if self.getGuessedStatus(letterIndex) == False:
                return False
        return True

#return dictionary length : returns int number of words
def dictionaryLength(dictionaryFile):
    lineStorage = dictionaryFile.readlines()
    #read the number of characters and words
    numberOfWords = 0
    for index in lineStorage:
        for character in index:
            if character == " ":
                numberOfWords += 1
    #print("Number Words=", numberOfWords)
    return numberOfWords

#return a string with the word display for canvas
def wordDisplay():
    string = ""
    for index in range(len(game.getWord())):
        if game.getGuessedStatus(index):
            string += game.getLetter(index)
        else:
            string += "*"
    return string

def addPicture(strikes, canvas): #draws the hanged man depending on how many strikes have accumulated
    if strikes == 1:
        canvas.create_line(200, 50, 200, 70)
    elif strikes == 2:
        canvas.create_oval(150, 70, 250, 100)
    elif strikes == 3:
        canvas.create_line(200, 100, 120, 150)
    elif strikes == 4:
        canvas.create_line(200, 100, 280, 150)
    elif strikes == 5:
        canvas.create_line(200, 100, 200, 210)
    elif strikes == 6:
        canvas.create_line(200, 210, 120, 300)
    elif strikes == 7:
        canvas.create_line(200, 210, 280, 300)
    canvas.update()

'''
---------------------------main-------------------------------
'''
#draw the initial windows
tk = Tk()
canvas = Canvas(tk, width = 400, height = 400, bg = "white")
canvas.pack()
canvas.focus_set()


playAgain = True
while playAgain:
    
    #initialize game
    game = gameStatus()
    player = playerStatus()
    canvas.delete("all")
    canvas.create_rectangle(15, 395, 115, 375)
    canvas.create_line(65, 375, 65, 50)
    canvas.create_line(65, 50, 200, 50)
    wordMessage = canvas.create_text(200, 345, font="Times 20", text=("Word:", wordDisplay()))
    incMessage = canvas.create_text(200, 370, font="Times 20", text=("Incorrects:", player.incorrectString()))
    topMessage = canvas.create_text(200, 25, font="Times 20", text=("Enter your next guess."))

    #game loop
    while not(game.winnerWinnerChickenDinner() or player.lostGame()):
        
        #input next guess
        canvas.itemconfig(topMessage, text="Enter your next guess.")
        canvas.update()
        guess = input("Input: ")
        while len(guess) > 1 or len(guess) < 0: #input validation
            canvas.itemconfig(topMessage, text="Incorrect input. Enter again.")
            canvas.update()
            guess = input("Input: ")
        while guess in player.getIncorrect(): #check if letter has already been guessed
            canvas.itemconfig(topMessage, text="Already guessed that. Enter again.")
            canvas.update()
            guess = input("Input: ")
            
        #calculate and display result
        if guess in game.getWord(): #on correct guess
            canvas.itemconfig(topMessage, text="Correct guess!")
            game.setGuessedStatus(guess)
        else: #on incorrect guess
            canvas.itemconfig(topMessage, text="Incorrect guess.")
            player.incrementStrikes()
            player.appendIncorrect(guess)
            addPicture(player.getStrikes(), canvas)
        canvas.itemconfig(wordMessage, text=("Word:", wordDisplay()))
        canvas.itemconfig(incMessage, text=("Incorrects:", player.incorrectString()))
        canvas.update()

    #Print win/lose    
    if game.winnerWinnerChickenDinner():
        canvas.itemconfig(topMessage, text="You win!")
    else:
        canvas.itemconfig(topMessage, text="You lose.")
        canvas.itemconfig(wordMessage, text=("Word:", game.getWordString()))
    canvas.update()
    time.sleep(5)
    

    #play again?
    canvas.itemconfig(topMessage, text="<Enter> to play again.")
    canvas.update()
    input("<Enter> to play again.")
