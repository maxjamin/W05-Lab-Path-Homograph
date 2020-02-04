#include <iostream>
#include <list>
#include <cstring>
#define  MaxNum 100
/***********************************************************************
* Program:
*    Lab 05, Homographs
*    Brother Helfrich, CS 370
* Author:
*    John Miller
*    Bretton Steiner
*    Henrique Vaz
*    Tyler Starr
*    Ben Smith
* Summary:
*    Enter a brief description of your program here!
 ************************************************************************/

/***********************************************************************
* Function:
*    HomographsTest()
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
* Summary:
*    Get the userinput and pass to parameter. 
 ************************************************************************/
int parseUserInput(char *userInput, std::list<std::string> *parsedUserInput)
{

  char tempCopyArray[MaxNum];
  int counterForCopy = 0;
  
  for(int i=0; i <= std::strlen(userInput); i++)
    {
      std::cout << userInput[i] << " " << std::strlen(userInput) << "\n";

      //if new / is encountered add new char array to list and set counter to zero
      if((userInput[i] == '/' && counterForCopy != 0) || i == std::strlen(userInput))
      {
	std::string str(tempCopyArray, counterForCopy);
	
	std::cout << "Str " << str << " Size " << counterForCopy << "\n";
	parsedUserInput->push_front(str);

	//clean the temp array
        for(int x=0; x < std::strlen(tempCopyArray);x++)
	  {
	    tempCopyArray[x] = '\0';
	  }
	counterForCopy = 0;
	
	
      } //increment temp array if 1st [] isn't /
      else if(userInput[i] != '/')
      {
	tempCopyArray[counterForCopy] = userInput[i];
	counterForCopy++;
      }
    }

   
  

  
  return 0;
}
/***********************************************************************
 **********************************************************************/
int Canonicalization()
{
  return 0;
}

/***********************************************************************
* Function:
*    main()
* Summary:
*    Enter a brief description of the function.
 ************************************************************************/
int main()
{
  char userInput[MaxNum];
  std::list<std::string> parsedUserInput;
  
  getUserInput(userInput);
  parseUserInput(userInput, &parsedUserInput);

  /*Testing output of userinput into list*/
  std::list<std::string>::iterator itt = parsedUserInput.begin();
  for(; itt != parsedUserInput.end(); itt++)
    std::cout << *itt << " \n";
  
  return 0;
}
