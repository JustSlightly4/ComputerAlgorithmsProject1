#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Compute average of a vector of doubles
double average(const vector<double>& times) {
    double sum = 0.0;
    for (double t : times) sum += t;
    return sum / times.size();
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage Error: ./a.out filename.txt\n";
    }
    string filename = argv[1];
    ifstream infile(filename); // replace with your filename
    if (!infile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    map<string, map<long long, vector<double>>> heapData;

    string line, currentHeap;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        // Check if the line is a heap name (does not contain ':')
        if (line.find(':') == string::npos) {
            currentHeap = line;
            continue;
        }

        // Parse line like "1000000: 0.192619"
        stringstream ss(line);
        long long size;
        char colon;
        double time;
        ss >> size >> colon >> time;

        heapData[currentHeap][size].push_back(time);
    }

    infile.close();

    // Print averages
    cout << fixed << setprecision(6);
    cout << "Average Insertion Times (seconds):\n";

    for (const auto& heapPair : heapData) {
        const string& heapName = heapPair.first;
        cout << heapName << ":\n";

        for (const auto& sizePair : heapPair.second) {
            long long size = sizePair.first;
            const vector<double>& times = sizePair.second;
            cout << " " << size << ": " << average(times) << "\n";
        }
        cout << "\n";
    }

    return 0;
}