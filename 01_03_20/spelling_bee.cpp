#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

bool isSubset(const string& sub, const string& super){
    /* Test whether string sub is a subset or equal set to super */
    int i = 0;
    int j = 0;
    for (i = 0; i<sub.length(); i++){
        for (j = 0; j<super.length(); j++){
            // if at any point there is no break below, then sub is not a subset
            if (sub[i] == super[j]) break;
        }
        if (j == super.length()) return 0;
    }
    return 1;
}

string stringUnique(const string& str){
    /* Return a new string with only of the unique letters in the string */
    int test_array[26] = {0};
    for (int i=0; i<str.length(); i++){
        test_array[int(str[i]) - int('a')] = 1;
    }
    int num_unique = 0;
    for (int i=0; i<26; i++) num_unique += test_array[i];
    char new_string[num_unique + 1];
    new_string[num_unique] = '\0';
    int j = 0;
    for (int i=0; i<26; i++){
        if (test_array[i]){
            new_string[j] = char(i + int('a'));
            j += 1;
        }
    }
    return string(new_string);
}

int numUnique(const string& str){
    /* Return the number of the unique letters in the string */
    int test_array[26] = {0};
    for (int i=0; i<str.length(); i++){
        test_array[int(str[i]) - int('a')] = 1;
    }
    int num_unique = 0;
    for (int i=0; i<26; i++) num_unique += test_array[i];
    return num_unique;
}


int wordScore(const string& jumble, const char central_letter, const string& word,
        bool print_words){
    /* Check the score of the word according to Spelling Bee rules
     *
     * Returns 0 if invalid word
     *
     * jumble: point to 7-letter letters for anagraming
     * central_letter: the central mandatory character
     * word: the word to score
     * print_words: whether to print the words that have score > 0
     */

    int score;
    if (word.length() < 4 || word.find(central_letter) == -1 
            || !isSubset(word, jumble)) return 0;
    else {
        score = word.length();
        // only check pangram for sufficiently long words
        if (score >= 7){
            if (numUnique(word) == 7) score += 7;
        }
    }
    if (print_words) cout << word << endl;
    return score;
}

// used to return both the score and number of words that counted towards the score
struct result{
    int score, count;
};

result totalScore(const string& jumble, const char central_letter, const vector<string>& word_list,
        bool print_words){
    /* Check the score of all words in word_list according to Spelling Bee rules
     *
     * jumble: point to 7-letter letters for anagraming
     * central_letter: the central mandatory character
     * word: the word to score
     * print_words: whether to print the words that have score > 0
     *
     * returns a result struct, with members score (the total score) and
     * count (the number of scored words)
     */
    result theresult;
    theresult.score = 0;
    theresult.count = 0;
    for(int i=0; i<word_list.size(); i++){
        int temp_score = wordScore(jumble, central_letter, word_list[i], print_words);
        theresult.score += temp_score;
        if (temp_score > 0) theresult.count += 1;
    }
    return theresult;
}

int main(){

    vector<string> word_list;
    ifstream wordfile ("word_list.txt");
    if (wordfile.is_open()){
        string str;
        int j = 0;
        while (wordfile >> str){
            word_list.push_back(str);
        }
        wordfile.close();
    } else cout << "Unable to open file" << endl;

    int len_all =  word_list.size();

    int len_culled = 0;

    vector<string> word_list_culled;
    for (int i=0; i<word_list.size(); i++){
        if (word_list[i].find("s") != string::npos || word_list[i].length() < 4){
            len_culled += 1;
        } else word_list_culled.push_back(word_list[i]);
    }
    
    /* Since the beehive must produce at least one pangram, then it must be comprised of
     * the letters from a word of >= 7 letters that has exactly 7 unique letters. We narrow
     * candidates from the word_list to satisfy these criteria
     */
    vector<string> candidates;
    for (int i=0; i<word_list_culled.size(); i++){
        if (word_list_culled[i].length() >= 7 && numUnique(word_list_culled[i]) == 7){
            string unique_string = stringUnique(word_list_culled[i]);
            // make sure not to add a duplicate
            bool add_string = 1;
            for (int j=0; j<candidates.size(); j++){
                if (unique_string == candidates[j]){
                    add_string = 0;
                    break;
                }
            }
            if (add_string) candidates.push_back(stringUnique(word_list_culled[i]));
        }
    }

    time_t start, end;
    time(&start);
    string current_jumble = "none";
    int current_total = 0;
    char current_central = 'a';
    for (int i=0; i<candidates.size(); i++){
        if (i % 1000 == 0) cout << 100.0 * float(i) / candidates.size() << " \% done" << endl;
        for (int j=0; j<7; j++){
            result temp_result = totalScore(candidates[i], candidates[i][j], word_list, 0);
            if (temp_result.score > current_total){
                current_jumble = candidates[i];
                current_total = temp_result.score;
                current_central = candidates[i][j];
            }
        }
    }
    time(&end);

    cout << "Main loop took " << end - start << " seconds" << endl;

    cout << current_jumble << endl;
    cout << current_total << endl;
    cout << current_central << endl;
    

    //cout << len_culled << endl;
    //cout << len_all << endl;
    
    
return 0;
}
