"""
Created on Jun 14, 2017

@author: uidp8103
"""

from fuzzywuzzy import fuzz


class StringFuzzMatch:
    def __init__(self):
        testArray = []

    # fuzzy_match between two strings
    def fuzzy_match(self, stringA, stringB):
        # remove all space, tab and \n
        stringA = stringA.replace("\n", "")
        stringA = stringA.replace(" ", "")
        stringA = stringA.replace("    ", "")
        stringA = stringA.lower()
        stringB = stringB.replace("\n", "")
        stringB = stringB.replace(" ", "")
        stringB = stringB.replace("    ", "")
        stringB = stringB.lower()
        if stringA == stringB:
            print("string matched!")
            return True
        else:
            print("string isn't matched!")
            return False

    # fuzzy_match between two strings Array
    def fuzzy_match_array(self, ListA, ListB, matchDegree):
        matchedAtoB = []
        matchedBtoA = []
        for stringA in ListA:
            mostmath = 0
            for value in ListB:
                if mostmath < fuzz.ratio(value, stringA):
                    mostmath = fuzz.ratio(value, stringA)
            if mostmath > matchDegree:
                for value in ListB:
                    if mostmath == fuzz.ratio(value, stringA):
                        matchedAtoB.append([value, stringA, str(mostmath)])
        for stringB in ListB:
            mostmath = 0
            for value in ListA:
                if mostmath < fuzz.ratio(value, stringB):
                    mostmath = fuzz.ratio(value, stringB)
            if mostmath > matchDegree:
                for value in ListA:
                    if mostmath == fuzz.ratio(value, stringB):
                        matchedBtoA.append([stringB, value, str(mostmath)])
        matchedList = [val for val in matchedAtoB if val in matchedBtoA]
        return matchedList
