#include <iostream>
#include <unistd.h> 
#include <list>
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#define MaxNum 1000
#define	forbiddenPath "./../W05-Lab-Path-Homograph/password.txt"
/***********************************************************************
* Program:
*    Lab 05, Homographs
*    Brother Helfrich, CS 370
* Author:
*    John Miller
*    Bretton Steiner
*	 Ben Smith
*    Tyler Starr
*
* Summary:
*    Enter a brief description of your program here!
 ************************************************************************/

/***********************************************************************
* Function:
*    HomographsTest()
* Inputs:
* Summary:
*    Enter a brief description of the function.
 ************************************************************************/
int HomographsTest()
{

  return 0;
}

/***********************************************************************
* Function:
*    NonHomographsTest()
* Inputs:
* Summary:
*    Enter a brief description of the function.
 ************************************************************************/
int NonHomographsTest()
{

  return 0;
}

/***********************************************************************
* Function:
*    getUserInput()
* Inputs: char pointer
* Summary:
*    Get the userinput and pass to parameter. 
 ************************************************************************/
int getUserInput(char *userInput)
{
  std::cout << "Please enter a filepath: ";
  std::cin>> userInput;
  return 0;
}

/***********************************************************************
* Function:
*    ParseUserInput()
* Inputs: char pointer, list<String> by pointer, int Direct of traversal for pushing onto the list
* Summary:
*    Place userInputs into a list.  
 ************************************************************************/
int parseInput(char *userInput, std::list<std::string> *parsedUserInput, int pushDirection)
{

  char tempCopyArray[MaxNum];
  int counterForCopy = 0;
  
  for(int i=0; i <= std::strlen(userInput); i++)
    {
      //std::cout << userInput[i] << " " << std::strlen(userInput) << "\n";
      //if new / or \ is encountered add new char array to list and set counter to zero
      if(((userInput[i] == '/' && counterForCopy != 0) || i == std::strlen(userInput)) ||
      	((userInput[i] == '\\' && counterForCopy != 0) || i == std::strlen(userInput)))
      {

		std::string str(tempCopyArray, counterForCopy);
		// If file path starts with / erase the char "/"
		if(str[0] == '/')
			str.erase(str.begin());

		if(pushDirection)
			parsedUserInput->push_back(str);
		else
			parsedUserInput->push_front(str);

		//clean the temp array
	    for(int x=0; x < std::strlen(tempCopyArray);x++)
		{
			tempCopyArray[x] = '\0';
		}
		counterForCopy = 0;
	
      }
      //increment temp array if 1st [] isn't /
      else if(userInput[i] != '/' || userInput[i] != '\\')
      {
		tempCopyArray[counterForCopy] = userInput[i];
		counterForCopy++;
      }
    }

   
  

  
  	return 0;
}
/***********************************************************************
* Function: getCurrentDirectory
* Inputs: char array by reference
* Summary: get current directory in a char array. Based from:
https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
 **********************************************************************/
int getCurrentDirectory(char (&cwd)[MaxNum])
{
	std::cout << "test01\n";
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
    	//printf("Current working dir: %s\n", cwd);
   	} else {
       	perror("getcwd() error");
       	return 1;
   	}
  	return 0;
} 
/***********************************************************************
* Function: toLowerCase()
* Inputs: string 
* Summary: Converts a string to all lowercase values
 Based on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
 **********************************************************************/
std::string toLowerCase(std::string input)
{
  	//replace Uppercase with lowerCase
  	std::transform(input.begin(), input.end(), input.begin(),
    [](unsigned char c){ return std::tolower(c); });
	
	return input;
}

/***********************************************************************
* Function: canonicalization()
* Inputs: list<String> , pointer User Input, list<String> by pointer ,file 
* path of executable in list form
* first input userinput, second is the filepath of the Executable 
 **********************************************************************/
int canonicalization(std::list<std::string> *parsedUserInput, 
	std::list<std::string> *parsedCwd)
{
  	std::list<std::string>::reverse_iterator revIt;
  	std::list<std::string>::iterator cwdItt = parsedCwd->begin();
  	cwdItt++;

  	//loop backwards through parsedUserInput
  	for (revIt = parsedUserInput->rbegin(); 
  		revIt != parsedUserInput->rend(); revIt++)
	{
		//Replace all iterators with the value ".." from parsedCwd list
		if(*revIt == "..")
		{
			std::cout << "revit is " << *revIt << "\n";
			*revIt = *cwdItt;
			cwdItt++;
		}
		//Remove all "."
		else if(*revIt == ".")
  		{
  			/*After research of erase function w/ reverse iterator
  			from https://stackoverflow.com/questions/1830158/how-to-call-erase-with-a-reverse-iterator*/
  			parsedUserInput->erase( --(revIt.base()));
  			
  		}
  		else //convert iterators with Upper letters to lowerCase 
  		{	
  			std::string tempString = *revIt;
  			*revIt = toLowerCase(tempString);
  		}
	}
	return 0;
}

/***********************************************************************
* Function:
*    main()
* Inputs: none
* Summary:
*    Driver function for the program.
 ************************************************************************/
int main()
{
	char userInput[MaxNum];
	char cwd[MaxNum];
	std::list<std::string> parsedCwd;
  	std::list<std::string> parsedUserInput;
  
  	//get user input, place into list<String>
  	getUserInput(userInput);
  	parseInput(userInput, &parsedUserInput, 1);

  	//get directory to test against, place into list<String>
	getCurrentDirectory(cwd);
	parseInput(cwd, &parsedCwd, 0);

  	canonicalization(&parsedUserInput, &parsedCwd);

  	/*Testing output of userinput into list*/
  	std::cout << "..........Output from list: .......................\n";
  	std::list<std::string>::iterator itt = parsedUserInput.begin();
  	for(; itt != parsedUserInput.end(); itt++)
    	std::cout << *itt << " \n";


    //check if input against homoHomograph and non-Homograph function
    
  
  	return 0;
}
