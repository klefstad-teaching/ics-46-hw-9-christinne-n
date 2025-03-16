#include "ladder.h"

void error(string word1, string word2, string msg)
{
    cerr << "Error: " << msg << " with "<< word1 << ", " << word2 << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    if(abs((int)str1.size() - (int)str2.size()) > d)
        return false;
    int i = 0, j = 0;
    int diff = 0;
    while(i < (int)str1.size() && j < (int)str2.size()) 
    {
        if(str1[i] != str2[j]) 
        {
            diff++;
            if (str1.size() > str2.size())
            {
                i++;
            }
            else if (str1.size() < str2.size())
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
        else {
        i++;
        j++;
        }
    }
    diff+= (str1.size()-i) + (str2.size()-j);
    return diff <= d;
}
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word) //checks if they are the same
        {return {begin_word};}
    
    queue<vector<string>> ladder_queue; //ladder_queue = vector queue of string
    ladder_queue.push({begin_word});
    set<string> visited; //visited = set of strings
    visited.insert(begin_word);

    while(!ladder_queue.empty())
    {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop(); //ladder = ladder_queue.pop_front()
        string last_word = ladder.back(); //last element of ladder

        for(const string& word : word_list) 
        {
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end())
            {
                visited.insert(word);
                vector<string> new_ladder = ladder; //copy of ladder
                new_ladder.push_back(word);
                if(word == end_word)
                    return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {}; //return no ladder found
}
void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("Can't open input file");
    }
    string word;
    while(file >> word)
        word_list.insert(word);
    file.close();
}
void print_word_ladder(const vector<string>& ladder)
{
    if(ladder.empty())
    {
        cout << "No word ladder found.\n";
    }
    else
    {
        cout << "Word ladder found: ";
        for(size_t i = 0; i < ladder.size(); ++i)
        {
        cout << ladder[i] << " ";
        }
        cout<<"\n";
    }
}
#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder()
{
    set<string> word_list;

    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}