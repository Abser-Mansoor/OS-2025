#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* arg[]) {
        if (argc < 2) return 1;
        ifstream input_file(arg[1]);
        string line;
        if (!infile) {
        cerr << "Error: Could not open input file '" << input_file << "'." << endl;
        return 1;
        }
        while(getline(input_file,line)) { 
                arr[i] = atoi(line[0]); 
                i++;
        }
        return 0;
}


