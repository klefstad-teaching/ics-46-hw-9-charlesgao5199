#include "ladder.h"

void error(string word1, string word2, string msg){
    cout << "Error: " << msg << " for words: " << word1 << " and " << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    // If the strings are identical, the edit distance is 0.
    if (str1 == str2)
        return true;

    int len1 = str1.size();
    int len2 = str2.size();

    // If the difference in lengths exceeds the allowed threshold, it's not possible.
    if (std::abs(len1 - len2) > d)
        return false;

    int edits = 0;  // Count of differences encountered.
    int i = 0, j = 0;  // Pointers for each string.

    // Process both strings until one is exhausted.
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            // Increment the edit count.
            ++edits;
            if (edits > d)
                return false;

            // If lengths differ, move the pointer of the longer string.
            if (len1 > len2) {
                ++i;
            } else if (len1 < len2) {
                ++j;
            } else { // If lengths are the same, move both pointers (substitution case).
                ++i;
                ++j;
            }
        } else {
            // Characters match; move both pointers.
            ++i;
            ++j;
        }
    }

    // Add any remaining characters in either string as additional edits.
    edits += (len1 - i) + (len2 - j);

    return (edits <= d);
}

bool is_adjacent(const string& word1, const string& word2){
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    // Queue to store the ladders in progress (each ladder is a vector of words)
    queue<vector<string>> ladders;
    ladders.push({begin_word});

    // Set to track visited words to avoid cycles
    set<string> visited;
    visited.insert(begin_word);

    while (!ladders.empty()) {
        vector<string> current_ladder = ladders.front();
        ladders.pop();

        // Get the last word of the current ladder
        string last_word = current_ladder.back();

        // For each word in the dictionary, check if it is adjacent (differs by one letter)
        for (const auto& candidate : word_list) {
            if (is_adjacent(last_word, candidate)) {
                // Only consider words that haven't been visited yet
                if (visited.find(candidate) == visited.end()) {
                    visited.insert(candidate);

                    // Create a new ladder by appending the candidate word
                    vector<string> new_ladder = current_ladder;
                    new_ladder.push_back(candidate);

                    // If we've reached the end word, return the ladder immediately
                    if (candidate == end_word) {
                        return new_ladder;
                    }

                    // Otherwise, add the new ladder to the queue for further exploration
                    ladders.push(new_ladder);
                }
            }
        }
    }

    // If no ladder is found, return an empty vector
    return vector<string>();
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }
    
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    // No need to call file.close() explicitly as the ifstream destructor does it.
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found.\n";
    } else {
        cout << "Word ladder found: ";
        for (const auto& word : ladder)
            cout << word << " ";
        cout << "\n";
    }
}


#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}