#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* arg[]) {
        if (argc < 2) return 1;
        ifstream file(arg[1]);
        if (!file) { cout << "Error! Could not Open File."; return 1; }
        string line;
        while (getline(file,line)) {
                cout << line << endl;
        }
        file.close();
        return 0;
}
