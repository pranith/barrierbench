#!/usr/bin/python3

import sys;
import re;

def parse_section(filehandle):
    i = 0;
    for line in filehandle:
        #print("%s" % line, end=" ");
        if (i == 2):
            #print("%s" % line, end=" ");
            num_accesses = re.search(r'./fitsincache.exe (.*?)\'', line).group(1);
            num_accesses = re.sub(r' ',"", num_accesses); # remove whitespace
        if (i == 4):
            num_cycles = re.search(r'(.*?) cycles', line).group(1);
            num_cycles = re.sub(r',',"", num_cycles); # remove comma
            num_cycles = re.sub(r' ',"", num_cycles); # remove whitespace
        if (i == 5):
            num_inst = re.search(r'(.*?) instructions', line).group(1);
            num_inst = re.sub(r',',"", num_inst); # remove comma
            num_inst = re.sub(r' ',"", num_inst); # remove whitespace
        if (i == 6):
            num_cache_ref = re.search(r'(.*?) cache-references', line).group(1);
            num_cache_ref = re.sub(r',',"", num_cache_ref); # remove comma
            num_cache_ref = re.sub(r' ',"", num_cache_ref); # remove whitespace
        if (i == 7):
            num_cache_miss = re.search(r'(.*?) cache-misses', line).group(1);
            num_cache_miss = re.sub(r',',"", num_cache_miss); # remove comma
            num_cache_miss = re.sub(r' ',"", num_cache_miss); # remove whitespace
        if (i == 9):
            num_seconds = re.search(r'(.*?) seconds', line).group(1);
            num_seconds = re.sub(r',',"", num_seconds); # remove comma
            num_seconds = re.sub(r' ',"", num_seconds); # remove whitespace
            
        i = i+1;
        if (i == 11):
            print(num_accesses, num_cycles, num_inst, num_cache_ref, num_cache_miss, num_seconds);
            return True;

    return False;

def parse_data(filename):
    filehandle = open(filename, "r");
    while (parse_section(filehandle)):
        pass

def main():
    if (len(sys.argv) == 1):
        print("Missing input data file");
        return;

    datafile = str(sys.argv[1]);
    parse_data(datafile);
    return;

if __name__ == "__main__":
    main();
