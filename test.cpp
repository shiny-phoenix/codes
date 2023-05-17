#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    ifstream input_file("word.txt");
    ofstream output_file("output_file.txt");
    unordered_set<string> unique_words;
    string word;

    if (input_file.is_open() && output_file.is_open()) {
        while (input_file >> word) {
            if (unique_words.find(word) == unique_words.end()) {
                unique_words.insert(word);
                output_file << word << " ";
            }
        }
        cout << "Duplicate words removed successfully." << endl;
        cout << "Total number of words: " << unique_words.size() << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }

    input_file.close();
    output_file.close();
    return 0;
}
