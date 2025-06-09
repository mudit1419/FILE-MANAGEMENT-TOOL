#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string compressRLE(const string& data) {
    string result;
    int count = 1;

    for (size_t i = 1; i <= data.length(); ++i) {
        if (i < data.length() && data[i] == data[i - 1]) {
            count++;
        } else {
            result += to_string(count) + data[i - 1];
            count = 1;
        }
    }

    return result;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "❌ Cannot open input.txt\n";
        return 1;
    }

    string content((istreambuf_iterator<char>(inputFile)),
                   istreambuf_iterator<char>());
    inputFile.close();

    string compressed = compressRLE(content);

    ofstream outputFile("compressed.txt");
    if (!outputFile) {
        cerr << "❌ Cannot write compressed.txt\n";
        return 1;
    }

    outputFile << compressed;
    outputFile.close();

    cout << " Compression done. Check compressed.txt\n";
    return 0;
}
