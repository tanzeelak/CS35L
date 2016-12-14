#!/usr/bin/python

import random, sys
from optparse import OptionParser

version_msg = "%prog 2.0"
usage_msg = """%prog [OPTION]... FILE

Output randomly selected lines from FILE."""

parser = OptionParser(version=version_msg, 
                          usage=usage_msg)

parser.add_option("-1",
                  action="store_true", dest="dash1", default=0,
                  help="choose 123") 
parser.add_option("-2",
                  action="store_true", dest="dash2", default=0,
                  help="output NUMLINES lines (default 1)") 
parser.add_option("-3",
                  action="store_true", dest="dash3", default=0,
                  help="output NUMLINES lines (default 1)") 
parser.add_option("-u",
                  action="store_true", dest="dashu", default=0,
                  help="output NUMLINES lines (default 1)") 

options, args = parser.parse_args(sys.argv[1:])

dash1 = int(options.dash1)
dash2 = int(options.dash2)
dash3 = int(options.dash3)
dashu = int(options.dashu)

table = []

class comm:
    def __init__(self, filename, filename2):
        f1 = open(filename, 'r')
        f2 = open(filename2, 'r')
        self.lines1 = f1.readlines()
        self.lines2 = f2.readlines()
        f1.close()
        f2.close()
    def printStuff(self):
        print ("printing from printStuff")
        print ("LINEZ 1 ORIG")
        print (self.lines1)
        print ("LINEZ 2 ORIG")
        print (self.lines2)
    def printTable(self):
#        print ("THE TABLE!")
        for w in table:
            if '\n' in w:
                w = w[:-1]
            print (w)

    def sort(self):
        i = 0
        j = 0
        k = 0
        while i < len(self.lines1):
            j = 0
            while j < len(self.lines2):
                if self.lines1[i] == self.lines2[j]:
                    if (dash3 == False):
                        if (dash1 == True and dash2 == True):
                            table.append(self.lines1[i])
                        elif (dash1 == True or dash2 == True):
                            table.append("\t" + self.lines1[i])
                        else:
                            table.append("\t\t" + self.lines1[i])
                    self.lines2.pop(j)
                    break
                if ( (j+1) >= len(self.lines2) and dash1 == False):
                    table.append(self.lines1[i])
                j+=1
            i+=1
        if (dash2 == False):
            while k < len(self.lines2):
                if (dash1 == True):
                    table.append(self.lines2[k])
                else:
                    table.append("\t" + self.lines2[k])
                k+=1

    def sortSorted(self):
        m = 0
        n = 0
        while m < len(self.lines1) and n < len(self.lines2):
            if self.lines1[m] == self.lines2[n]:
                if (dash3 == False):
                    if (dash1 == True and dash2 == True):
                        table.append(self.lines1[m])
                    elif (dash1 == True or dash2 == True):
                        table.append("\t" + self.lines1[m])
                    else:
                        table.append("\t\t" + self.lines1[m])
                n+=1
                m+=1
            elif self.lines1[m] < self.lines2[n]:
                if (dash1 == False):
                    table.append(self.lines1[m])
                m+=1
            elif self.lines1[m] > self.lines2[n]:
                if (dash2 == False):
                    if (dash1 == True):
                        table.append(self.lines2[n])
                    else:
                        table.append("\t" + self.lines2[n])
                n+=1
        if (dash1 == False):
            while m < len(self.lines1):
                table.append(self.lines1[m])
                m+=1
        if (dash2 == False):
            while n < len(self.lines2):
                if (dash1 == True):
                    table.append(self.lines2[n])
                else:
                    table.append("\t" + self.lines2[n])
                n+=1

def main():
#    version_msg = "%prog 2.0"
#    usage_msg = """%prog [OPTION]... FILE

#Output randomly selected lines from FILE."""

#    parser = OptionParser(version=version_msg, 
#                          usage=usage_msg)

#    parser.add_option("-n", "--numlines",
#                      action="store", dest="numlines", default=1,
#                      help="output NUMLINES lines (default 1)") 
#    options, args = parser.parse_args(sys.argv[1:]) 
    
    
#    try:
#        numlines = int(options.numlines)
#    except:
#        parser.error("invalid NUMLINES: {0}".
#                     format(options.numlines))
#    if numlines < 0:
#        parser.error("negative count: {0}".
#                     format(numlines))
    if len(args) != 2:
        parser.error("wrong number of operands") 
    input_file = args[0]
    input_file2 = args[1]
        
    try:
        generator = comm(input_file, input_file2)
#        generator.printStuff()
        if dashu == True:
            generator.sort()
        else:
            generator.sortSorted()
        generator.printTable()
    except IOError as err:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
        
if __name__ == "__main__":
    main()

