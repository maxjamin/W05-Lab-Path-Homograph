#include <iostream>
#include <unistd.h> 
#include <list>
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#define MaxNum 1000
#define	forbiddenPath "../W05-Lab-Path-Homograph/password.txt"
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
int parseUserInput(char *userInput, std::list<std::string> *parsedUserInput, int pushDirection)
{

  char tempCopyArray[MaxNum];
  int counterForCopy = 0;
  
  for(int i=0; i <= std::strlen(userInput); i++)
    {
      //std::cout << userInput[i] << " " << std::strlen(userInput) << "\n";
      //if new / is encountered add new char array to list and set counter to zero
      if((userInput[i] == '/' && counterForCopy != 0) || i == std::strlen(userInput))
      {
		std::string str(tempCopyArray, counterForCopy);

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
* Function: getCurrentDirectory
* Summary:
* get current directory in a char array. Based from:
https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
 **********************************************************************/
int getCurrentDirectory(char (&cwd)[100])
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
* Based on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
 **********************************************************************/
std::string toLowerCase(std::string input)
{
  	//replace Uppercase with lowerCase
  	std::transform(input.begin(), input.end(), input.begin(),
    [](unsigned char c){ return std::tolower(c); });
	
	return input;
}

/***********************************************************************

 **********************************************************************/
int canonicalization(std::list<std::string> *parsedUserInput)
{
	char cwd[100];
	std::list<std::string> parsedCwd;
	getCurrentDirectory(cwd);
	parseUserInput(cwd, &parsedCwd, 0);

	printf("Current working dir: %s\n", cwd); 

	//iterate through the list of userInput
	std::list<std::string>::iterator itt = parsedUserInput->begin();
	std::list<std::string>::iterator itt2 = itt;
	std::list<std::string>::iterator cwdItt = parsedCwd.begin();

	std::cout << "................ 1 Output from list: \n";
  	std::list<std::string>::iterator cwdIttt = parsedCwd.begin();
  	for(; cwdIttt != parsedCwd.end(); cwdIttt++)
    	std::cout << *cwdIttt << " \n";


  	LOOP:for(; itt != parsedUserInput->end(); itt++)
  	{

  		std::cout << "Itt is " << *itt << "\n";
  		//for the /./ replace with working directory
  		if("." == *itt)
  		{
  			itt = parsedUserInput->erase(itt);
  			goto LOOP; //not pretty but skip to start of next loop
  		}
  		//for the /../ replace with parent working directory
  		else if(".." == *itt)
  		{
    		std::cout << "Itts starting point " << *itt << "\n";
  			/*check to see if next is .. or not, if not then add 
  			the values to the parsedUserInput list*/
  			itt2 = itt;
  			if(*++itt2 != "..")
  			{
				
  				std::list<std::string>::iterator tempitt = itt;
  				std::list<std::string>::iterator tempCwd = cwdItt;
  				std::list<std::string>::iterator theEnd = parsedUserInput->begin();
  				--theEnd;
  				for(; tempitt != theEnd; tempCwd--, tempitt--)
  				{
  					//convert to lowerCase
  					std::string tempString = *tempCwd;
  					*tempitt = toLowerCase(tempString);
  				}

  			}
  			cwdItt++;

  		}
  		else
  			//convert to lowerCase 
  		{	std::string tempString = *itt;
  			*itt = toLowerCase(tempString);
  		}


  	}

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
  	parseUserInput(userInput, &parsedUserInput, 1);

  	canonicalization(&parsedUserInput);

  	/*Testing output of userinput into list*/
  	std::cout << "..........Output from list: .......................\n";
  	std::list<std::string>::iterator itt = parsedUserInput.begin();
  	for(; itt != parsedUserInput.end(); itt++)
    	std::cout << *itt << " \n";
  
  	return 0;
}
