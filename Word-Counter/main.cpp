//-- Include Needed Libraries
# include <iostream>
# include <fstream>
# include <vector>
# include <string>

//-- Methodes Prototype
bool isLetter(char &);
bool isSeparator(char &);

//-- Class Definition
class Words {
    private:
        //-- List of Words
        std::vector<std::string> word;
        //-- List of Files with Words
        std::vector<std::vector<std::string>> file;
        //-- Name of Host List
        std::vector<std::string> listName;
        //-- Number of Host List
        std::vector<int> listNumber;
        //-- Count of each Word
        std::vector<int> count;
        //-- Amount of Words
        int amount, totalAmount;
    public:
        //-- Constructor
        Words() {word.resize(0); file.resize(0); listName.resize(0); listNumber.resize(0); count.resize(0); amount = 0; totalAmount = 0;}
        //-- Method to Set Words Data
        void add(std::string &, std::string &, int &);
        //-- Method to Get Amount of Words
        int getAmount() {return amount;} 
        //-- Method to Get Words
        std::string getWord(int &index) {return word[index];}
        //-- Method to Display Words
        void display() {
            for (int i = 0; i < amount; i++) {
                std::cout << word[i] << std::endl;
            }
        }
        //-- Method to Get each Word's Amount
        void countWords();
        //-- Method to Display Counts of Words
        void displayCounts() {
            for (int i = 0; i < amount; i++) {
                std::cout << word[i] << " : " << count[i] << " Times" << std::endl; 
            }
        }
};

//-- Method to Add Words Data
void Words::add(std::string &inputWord, std::string &inputList, int &inputIndex) {
    listNumber.push_back(inputIndex);
    listName.push_back(inputList);
    word.push_back(inputWord);
    amount++;
}

//-- Method to Get each Word's Amount
void Words::countWords() {
    //-- Initialize Count List
    for (int i = 0; i < amount; i++) {
        count.push_back(0);
    }
    //-- Count Words
    for (int i = 0; i < amount; i++) {
        for (int j = 0; j < amount; j++) {
            if (word[i] == word[j]) {
                count[i] += 1;
            }
        }
    }
}

//-- Method to Check If Character is Letter
bool isLetter(char &input) {
    return (input >= 65 && input <= 90) || (input >= 97 && input <= 122) || (input == '\'');
}

int main() {
    //-- Start of Word Flag
    bool start = false;
    //-- Amount of Files
    int amount = 0;
    //-- Word List
    Words words;
    //-- Menu
    std::cout << "Howmany Document Files ? "; std::cin >> amount;
    std::string filename;
    char character;
    std::string word;
    word.resize(0);
    for (int i = 0; i < amount; i++) {
        std::cout << "Enter File " << i + 1 << "'s Name : "; std::cin >> filename;
        std::fstream file(filename, std::fstream::in);
        if (!file.is_open()) {
            std::cout << "- Error : Can't Find File with Name : " << filename << std::endl;
            i--;
        } else {
            while (file >> std::noskipws >> character) {
                if (isLetter(character)) {
                    if (start == false) {
                        start = true;
                    }
                    word.push_back(character);
                } else {
                    if (start == true) {
                        start == false;
                        words.add(word, filename, i);
                        std::cout << " - Added Word --> " << word << std::endl;
                        word.clear();
                    }
                }
            }
            //-- Add Last Word
            words.add(word, filename, i);
            std::cout << " - Added Word --> " << word << std::endl;
            word.clear();
        }
    }
    words.countWords();
    words.displayCounts();
    return 0;
}
