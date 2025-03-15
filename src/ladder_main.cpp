#include "ladder.h"

int main()
{
    set<string> word_ladd;
    load_words(word_ladd, "src/words.txt");

    cout <<"Creating word ladder..." << endl;
    string first, last;
    cout << "What is the first word?: " ;
    cin >> first;
    cout << "What is the last word?: ";
    cin >> last;

    vector<string> myladder = generate_word_ladder(first, last, word_ladd);
    print_word_ladder(myladder);

    return 0;

}