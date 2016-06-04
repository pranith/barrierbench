#!/usr/bin/python

import os;
import sys;
import re;
import matplotlib.pyplot as plt;
import numpy as np;
import itertools;

result_names = list();
accesses_cycles = list();
accesses_ipc = list();
tmp_cycles = list();
tmp_ipc = list();
markers = ('^', '+', 'v', 'o', '*');

def clean_num(number):
    number = re.sub(r',',"", number); # remove comma
    number = re.sub(r' ',"", number); # remove whitespace
    return number;

def parse_section(filehandle):
    i = 0;
    for line in filehandle:
        #print("%s" % line, end=" ");
        if (i == 2):
            #print("%s" % line, end=" ");
            num_accesses = re.search(r'./fitsincache.exe (.*?)\'', line).group(1);
            num_accesses = clean_num(num_accesses);
        if (i == 4):
            num_cycles = re.search(r'(.*?) cycles', line).group(1);
            num_cycles = clean_num(num_cycles);
        if (i == 5):
            num_inst = re.search(r'(.*?) instructions', line).group(1);
            num_inst = clean_num(num_inst);
        if (i == 6):
            num_cache_ref = re.search(r'(.*?) cache-references', line).group(1);
            num_cache_ref = clean_num(num_cache_ref);
        if (i == 7):
            num_cache_miss = re.search(r'(.*?) cache-misses', line).group(1);
            num_cache_miss = clean_num(num_cache_miss);
        if (i == 9):
            num_seconds = re.search(r'(.*?) seconds', line).group(1);
            num_seconds = clean_num(num_seconds);
            
        i = i+1;
        if (i == 11):
            tmp_cycles.append(num_cycles);
            tmp_ipc.append(float(num_inst)/float(num_cycles));
            #print(num_accesses, num_cycles, num_inst, num_cache_ref, num_cache_miss, num_seconds);
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

    num_files = len(sys.argv);

    index = 1;
    while (index < num_files):
        datafile = str(sys.argv[index]);
        parse_data(datafile);
        accesses_cycles.append(list(tmp_cycles));
        del tmp_cycles[:];
        accesses_ipc.append(list(tmp_ipc));
        del tmp_ipc[:];
        result_names.append(os.path.splitext(datafile)[0]);
        index += 1;

    x = np.arange(1, 1+len(accesses_cycles[0]));
    # plot cycles
    index = 0;
    cycles_fig = plt.figure(1);
    plt.xlabel("Cache Misses Per Iteration");
    plt.ylabel("Cycles");
    imarker = itertools.cycle(markers);

    res_csv = dict();
    for i in range(0,len(accesses_ipc[0])):
        res_csv[i] = list();

    while (index < num_files - 1):
        plt.plot(x, accesses_cycles[index], label=result_names[index], marker =
                next(itertools.cycle(imarker)));
        for i in range(0, len(accesses_ipc[0])):
            res_csv[i].append(accesses_ipc[index][i]);
        index += 1;

    plt.legend(loc="upper right");

    # plot ipc
    index = 0;
    ipc_fig = plt.figure(2);
    plt.xlabel("Cache Misses Per Iteration");
    plt.ylabel("IPC");
    imarker = itertools.cycle(markers);
    while (index < num_files - 1):
        plt.plot(x, accesses_ipc[index], label=result_names[index], marker =
                next(itertools.cycle(imarker)));
        index += 1;

    plt.legend(loc="upper right");
    plt.show();

    # write parsed results to file
    res_file = open("result.csv", 'w');
    for i in range(0, len(accesses_ipc[0])):
        res_file.write(str(i) + ",");
        for j in range(0, len(res_csv[i])):
            res_file.write(str(res_csv[i][j]) + ",");
        res_file.write("\n");

    return;

if __name__ == "__main__":
    main();
