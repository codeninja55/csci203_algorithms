// Using a stringstreams to extract words from a line

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main ()
{
  string mystr,word;
  float price=0;
  int quantity=0;

  cout << "Enter words: ";
  getline (cin,mystr);
  stringstream ss(mystr);
  for(;;){
	  ss >> word;
	  if(ss.fail())break;
	  cout << word << endl;
	}
  cout << "End of program" <<  endl;
  return 0;
}
