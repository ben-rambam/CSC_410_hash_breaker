#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
//Right now the program needs to be called with the letters it is looking for

using namespace std;
//This is the Alphabet bet that will be used for the testing purposes
const char lowerCase[26] =
{
	'a', 'b', 'c', 'd', 'e', 'f', 'g',
	'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u',
	'v', 'w', 'x', 'y', 'z'
};

void victoryFormation(unsigned int length, string start, string hashSIN)
{
	if(length == 0) 
	{
		
		return;
		
	}

	for(unsigned int i = 0; i < 26; i++) 
	{
		int stopper;
		string temp = start + lowerCase[i];
		victoryFormation(length-1, temp, hashSIN);
		if( temp.compare(hashSIN) == 0)
		{
			string found = temp;
			cout << "The correct value is: " << found << endl; 
			
		}
		
	}
	
}
void beatClemson(string hashSIN)
{
	int length = 1;
	while(length < 4)
	{
		
		victoryFormation(length, "", hashSIN); //This hands off the length to vf function, gives an empty string to work with, and gives the expected value
		length++;
	}
}

int main(int argc, char* argv[])
{
	unsigned long long hashIN = atoll(argv[1]);
	string hashSIN = argv[2]; //I will play with this to see if I can get it right
	
	
	cout << "The input hash is " << hashIN << endl;
	
	//cout << "The expected letter values are: " << hashSIN << endl; //This is to ensure that the program can look for the correct hash
	beatClemson(hashSIN);
	return 0;
}