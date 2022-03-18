#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"
using namespace std;
void createBox();
void keyboardLayout(int x, int y);
void letterSelector();

int green=0;
void compareWord(string guess, string word);

int colorArr[6][5];
int guesses;

void update();
char arr1[10] = { 'Q','W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P' };
char arr2[9] = { 'A','S', 'D', 'F', 'G', 'H', 'J', 'K', 'L' };
char arr3[7] = { 'Z','X', 'C', 'V', 'B', 'N', 'M' };
bool updateText = false;
char arr[3][6] = {
        {char(201),char(205),char(205),char(205),char(187),' '}
        ,{char(186),' ',' ',' ',char(186),' '}
        ,{char(200),char(205),char(205),char(205),char(188),' '}
};
bool gameActive=1;
bool mainMenu = 1;
bool wordle=0;
bool validGuess=0;
int selectedY = 0;
int selectedX = 0;

vector<string> strings;
enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};
void update()
{
    system("CLS");
    createBox();
    cout << endl;
    cout << endl;
    cout << endl;
   
}
int main()
{
   
    srand(time(NULL));

    vector<string>words;
    fstream file;
    string word2;
    string filename = "words.txt";
    string guess;
    string word;
    file.open(filename.c_str());
    while (getline(file, word2))
    {
        words.push_back(word2);
    }
  

  
    while (gameActive == true)
    {
        int random = rand() % words.size();
        word = words[random];


         while (mainMenu)
         {
             cout << "Welcome to crazy wordle puzzle!" << endl;cout << "Type 1 for start" << endl; cout << "type 0 for exit" << endl;
             
             cin >> gameActive;

             if (cin.fail())
             {
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 system("CLS");
             }
             else
             {
                 if (gameActive == false){return 0;}

                 mainMenu = false;
                 wordle = true;

                 system("CLS");                 
                 createBox();
                 cout << endl;
                 cout << endl;
                 cout << endl;
             }
         
         }
 
        
         
            
         while (wordle)
         {
             //the word that is to be guessed
             //cout << word<<endl; 
             cout << "Guess a word: ";
             cin >> guess;
             for (int i = 0; i < guess.size(); i++)
             {
                 guess[i] = toupper(guess[i]);
             }
             for (int i = 0; i <words.size(); i++)
             {           
                  if (words[i].compare(guess)==0)
                  {
                     validGuess = 1;
                     strings.push_back(guess);
                     updateText = true;
                     compareWord(guess, word);
                     update();
                     guesses++;
                  }
             }
             if (validGuess == 0){cout << "Invalid input or word does not exist in list" << endl; green = 0;}
             validGuess = 0;
            
             if (green == 5)
             {
                
                 wordle = false;
                 
                 cout <<"You solved it!"<<endl << "Good job!" << endl;
                 system("PAUSE");
                 system("CLS");
                 strings.clear();
                 guesses = 0;
                 updateText = false;
                 mainMenu = true;
               
             }
        
             if (guesses == 6 && green != 5)
             {

                 wordle = false;

                 cout << "Game over you lost " << endl << "Good job!" << endl;
                 system("PAUSE");
                 system("CLS");
                 cin.clear();
                 strings.clear();
                 guesses = 0;
                 updateText = false;
                 mainMenu = true;
                 arr[1][2] = ' ';
                 
            
                 
                 
               
             
             }                         
         }
    }
  
    
  
   

      
        
      
    
  //cout << FOREGROUND(ForegroundColor::BrightRed, "Hello world!") << std::endl;
    //cout << BACKGROUND(BackgroundColor::BrightRed, "Hello world!") << std::endl;
}
void createBox()
{
   
    string str = "     ";;
    if (updateText == true)
    {
       //str= strings[0];
    }
 

    for (int y = 0; y < 6; y++)
    {
        if (updateText == true)
        {
            if (strings.size() > y)
            {
                str = strings[y];
            }
            else
            {
                str = "     ";
            }
           
        }
        for (int i = 0; i < 3; i++)
        {
            for (int x = 0; x < 5; x++)
            {
                for (int j = 0; j < 6; j++)
                {
                    if (updateText == true)
                    {
                        arr[1][2] = str[x];
                     
                    }
                    if (i == 1 && j == 2&& strings.size() > y)
                    {
                        
                        cout << BACKGROUND(colorArr[y][x], arr[i][j]);
                    }

                    else
                    {
                        cout << arr[i][j];
                    }
                    

                }
            }


            cout << endl;

        }
      
        
    }

}


void compareWord(string guess, string word)
{
    green = 0;

    for (int i = 0; i < 5; i++)
    {
        size_t pos = word.find(toupper(guess[i]));
        if (pos == string::npos) {
           
            colorArr[guesses][i] = 41;
           
        }
        else {
            colorArr[guesses][i] = 43;

            if (pos == i||toupper(guess[i])==word[i])
            {
                colorArr[guesses][i] = 42;
                green++;

            }
          
          
        }




    }


}
