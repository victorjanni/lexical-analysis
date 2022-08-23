#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;
class Lexical{
private:
        vector<string>lastState ;
	vector<string> letters;
	vector<map<string, string>> nextLine;
	vector<string> nextTokens;
	ifstream file;
	string start;
public:
        ~Lexical();
        Lexical(const string nameOfFile);
	bool forStatement(string str)const; // returns true if the word passed in is in the language defined by the DFA
        void tokenization(string str, vector<string> &tokens);
};
Lexical::~Lexical(){
}
Lexical::Lexical( string nameOfFile){



file.open(nameOfFile);
        if (file.is_open())
        {
        string line;
        string starting;
        string to;
        string ending;
        int index;
        getline(file, start);
        getline(file, line);
        tokenization(line, lastState);
        getline(file, line);
        tokenization(line, letters);
        nextLine.resize(letters.size());
        while (getline(file, line))
        {
        nextTokens.clear();
        tokenization(line, nextTokens);
        starting = nextTokens[0];
        to = nextTokens[1];
        ending = nextTokens[2];
                // find which index contains "to" in the vector "letter"
        for (unsigned int i = 0; i < letters.size(); ++i)
        {
          if (letters[i] == to)
          {
           index = i;
           break;
          }
        }
       // then map the string "starting" to "ending", in the map at index "index" in vector "nextLine".
            nextLine[index].insert(pair<string,string>(starting, ending));
        }
        file.close();
      }
        else
        {
         cout << "There is a error " << nameOfFile << endl;
	}
        }
void Lexical ::tokenization(string str, vector<string> &tokens)
 {
	istringstream ss(str);
	while (!ss.eof())
        {
	  string x;
	  getline( ss, x, ' ' );
	  tokens.push_back(x);
	}
 }
        bool Lexical::forStatement(string str) const {
	bool valid = true;
	string currentState = start;
	int index = 0;

       for (unsigned int i = 0; i < str.length(); i++)
      {
        auto it = find(letters.begin(), letters.end(), string(1, str[i]));
        if (it != letters.end())
        {
            index = it - letters.begin();
            if (nextLine[index].find(currentState) != nextLine[index].end())
           {
            currentState = nextLine[index].at(currentState);
           }
             else
           {
            valid = false;
            }
        }

         else
            {//cout << word[i] << " is not in the alphabet" << endl;
            valid = false;
            }
        }

        if (valid)
        {
			// if current state is a final state, word was valid
           auto it2 = find(lastState.begin(), lastState.end(), currentState);
           if (it2 != lastState.end())
            {
                   valid = true;
            } else
             {
                valid = false;
             }

         }
         else
         {
          valid = false;
          }

        return valid;
}
void lexicalAnalyze(string token, Lexical *IdentifierLexical, Lexical *integerLexical, Lexical *floatLexical, Lexical *stringLexical);
bool forWhitespace(char ch);
bool forDelimiter(char ch);
bool forOperator(char ch);
bool forComment(const string &str);
bool forKeyword(string token);

bool forIdentifier(string token, Lexical *lex);
bool forInteger(string token, Lexical *lex);
bool forFloat(string token, Lexical *lex);
bool forString(string token, Lexical *lex);
string stripSpaces(string str);
void lexicalAnalyze(string token, Lexical *IdentifierLexical, Lexical *integerLexical, Lexical *floatLexical, Lexical *stringLexical)
{
if (token.length() > 0) {
		if (forKeyword(token)) {
			cout  << left << token << right << "Keyword" << endl;
		} else if (forIdentifier(token, IdentifierLexical)) {
			cout  << left << token << right << "Identifier" << endl;
		} else if (forInteger(token, integerLexical)) {
			cout  << left << token << right << "Integer" << endl;
		} else if (forFloat(token, floatLexical)) {
			cout  << left << token << right << "Float" << endl;
		} else if (forString(token, stringLexical)) {
			cout  << left << token << right << "String Literal" << endl;
		}
		else
{
			cout  << left << token << right << "String" << endl;
		}
	}
}
string stripSpaces(string str) {
	string noSpaces;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			noSpaces.push_back(str[i]);
		}
	}
	return noSpaces;
	}
bool forWhitespace(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ',') {
		return true;
	} else {
		return false;
	}
}
bool forComment(const string &str)
{
  return str == "/*" || str == "//";
}
// returns true if the char argument is a special symbol
bool forDelimiter(char ch) {
	if (ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch ==';' || ch == '[' || ch == ']') {
		return true;
	} else {
		return false;
	}
}
// returns true if the char argument is an operator
bool forOperator(char ch)
{
 if (ch == '+' || ch == '-' || ch == '=' || ch == '/' || ch =='*' || ch =='%' || ch =='<' || ch=='>') {
        return true;
} else
        return false;
}

// c++ keyword
bool forKeyword(string token)
{
  if (token == "asm"||token == "auto" || token == "break" || token == "case" || token == "char" || token == "class" || token == "const"
  || token == "continue" || token == "do" || token == "double" || token == "else" || token == "enum" || token == "extern" || token == "float"
  || token == "for" || token == "friend" || token == "goto" || token == "if" || token == "inline" || token == "int" || token == "long"
  || token == "new" || token == "operator" || token == "private" || token == "protected" || token == "public" || token == "register" || token == "return"
  || token == "short" || token == "signed" || token == "sizeof"|| token=="static"||token=="struct"||token=="switch"||token=="template"||token=="this"||
  token=="this"||token=="throw"||token=="try"||token=="typedef"||token=="union"||token=="unsigned"||token=="virtual"||token=="void"||token=="volatile"
  ||token=="while"||token=="bool"||token=="dynamic_cast"||token=="explicit"||token=="export"||token=="false"||
  token=="mutable"||token=="export"||token=="namespace"||token=="reinterpret_cast"||token=="static_cast"||token=="true"||token=="typeid"||token=="typename"||
  token=="using"||token=="wchar_t")
  {
           return true;
   } else {
           return false;
	}
}

bool forIdentifier(string token, Lexical *lex)
{
   return lex->forStatement(token);
}
bool forInteger(string token, Lexical *lex)
{
  return lex->forStatement(token);
}

bool forFloat(string token, Lexical *lex)
{
  return lex->forStatement(token);
}
bool forString(string token, Lexical *lex)
{
  return lex->forStatement(stripSpaces(token));
}
int main()
{
      string Value;
      cout << "Enter the name of  txt file : " << endl;
      cin >> Value;
      ifstream file(Value);
      if (file.is_open())
     {
        string line;	// the line to be read in from file
        string token;	// the token to be analyzed
        char lookahead;	// char that looks ahead for spaces and symobls
        Lexical identifierLexical("identifier.txt");
        Lexical integerLexical("integer.txt");
        Lexical floatLexical("float.txt");
        Lexical stringLexical("string.txt");
        while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++)
        {
         lookahead = line[i];
        if (forWhitespace(lookahead)) {
					// token can be analyzed since we hit a whitespace
        lexicalAnalyze(token,  &identifierLexical,  &integerLexical,  &floatLexical, &stringLexical);

        token.clear();
                }
        else if (forDelimiter(lookahead))
        {
        // token can be analyzed since we hit a symbol
        lexicalAnalyze(token,  &identifierLexical,  &integerLexical,  &floatLexical, &stringLexical);;
        token.clear();
        cout << "<"<<left << lookahead << right<<">" << "Symbol" << endl;
        }


        else if (forOperator(lookahead))
        {
					// token can be analyzed since we hit an operator
         lexicalAnalyze(token,  &identifierLexical,  &integerLexical,  &floatLexical, &stringLexical);
         token.clear();
         cout << "("<<left << lookahead <<")"<< right << "Operator" << endl;
        }
        else if (lookahead == '"')
        {
        // token can be analyzed since we hit the start of a string
         lexicalAnalyze(token,  &identifierLexical,  &integerLexical,  &floatLexical, &stringLexical);
         token.clear();
         token.push_back(lookahead);
         i++;
         lookahead = line[i];
         while(lookahead != '"')
          {
          token.push_back(lookahead);
          i++;
          lookahead = line[i];
          }
          token.push_back(lookahead);
          }

            else
             {
                // didn't hit a delimiter, so append lookahead to token
                token.push_back(lookahead);
             }
        }

       }

	} else
	{
		cout << "Unable to open file " << Value<< endl;
	}

	return 0;
}


//bool forIdentifier(string ch)
//{
//    if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9'
//    ||ch=='a'||ch=='b'||ch=='c'||ch=='d'||ch=='e'||ch=='f'||ch=='g'||ch=='h'||ch=='i'||ch=='j'
//    ||ch=='k'||ch=='l'||ch=='m'||ch=='n'||ch=='o'||ch=='p'||ch=='q'||ch=='r'||ch=='s'||ch=='t'
//    ||ch=='u'||ch=='v'||ch=='w'||ch=='x'||ch=='y'||ch=='z'||ch=='A'||ch=='B'||ch=='C'||ch=='D'
//    ||ch=='E'||ch=='F'||ch=='G'||ch=='H'||ch=='I'||ch=='J'||ch=='K'||ch=='L'||ch=='M'||ch=='N'
//    ||ch=='O'||ch=='P'||ch=='Q'||ch=='R'||ch=='S'||ch=='T'||ch=='U'||ch=='V'||ch=='W'||ch=='X'||
//    ||ch=='Y'||ch=='Z')
//    {
//           return true;
//   } else {
//           return false;
//	}
//}






