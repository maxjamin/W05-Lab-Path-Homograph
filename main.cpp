#include <iostream>
#include <unistd.h> 
#include <list>
#include <stack>
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#define MaxNum 1000
#define	forbiddenPath "/home/readyone/Documents/school2/schoolWinter2020/cs470/W05-Lab-Path-Homograph"
/***********************************************************************
* Program:
*    Lab 05, Homographs
*    Brother Helfrich, CS 370
* Author:
*    John Miller
*    Bretton Steiner
*    Ben Smith
*    Tyler Starr 
*
* Summary:
*    Enter a brief description of your program here!
 ************************************************************************/

/***********************************************************************
* Function:
*    CannonsTest()
* Inputs:
* Summary:
*    Test cases for the cannocalization function
 ************************************************************************/
int CannonsTest()
{
	//
  	return 0;
}

/***********************************************************************
* Function:
*    HomographsTest()
* Inputs:
* Summary:
*    Test cases for pairs of homographs
 ************************************************************************/
int HomographsTest()
{
	//
  	return 0;
}

/***********************************************************************
* Function:
*    NonHomographsTest()
* Inputs:
* Summary:
*    Test cases for pairs which are not homographs
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
// int parseInput(char *userInput, std::stack<std::string> *parsedUserInput, int pushDirection)
// {

//   char tempCopyArray[MaxNum];
//   int counterForCopy = 0;
  
//   for(int i=0; i <= std::strlen(userInput); i++)
//     {
//       //std::cout << userInput[i] << " " << std::strlen(userInput) << "\n";
//       //if new / or \ is encountered add new char array to list and set counter to zero
//       if(((userInput[i] == '/' && counterForCopy != 0) || i == std::strlen(userInput)) ||
//       	((userInput[i] == '\\' && counterForCopy != 0) || i == std::strlen(userInput)))
//       {

// 		std::string str(tempCopyArray, counterForCopy);
// 		// If file path starts with / erase the char "/"
// 		if(str[0] == '/')
// 			str.erase(str.begin());

// 		if(pushDirection)
// 			parsedUserInput->push_back(str);
// 		else
// 			parsedUserInput->push_front(str);

// 		//clean the temp array
// 	    for(int x=0; x < std::strlen(tempCopyArray);x++)
// 		{
// 			tempCopyArray[x] = '\0';
// 		}
// 		counterForCopy = 0;
	
//       }
//       //increment temp array if 1st [] isn't /
//       else if(userInput[i] != '/' || userInput[i] != '\\')
//       {
// 		tempCopyArray[counterForCopy] = userInput[i];
// 		counterForCopy++;
//       }
//     }

//   	return 0;
// }

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
* Function: printStack()
* Inputs: stack of strings 
* Summary: prints the contents of the stack
 **********************************************************************/
void printStack(std::stack<std::string> stack)
{
  	std::stack<std::string> displayStack;
	while (stack.size() > 0)
	{
		displayStack.push(stack.top());
		stack.pop();
	}

	// Print off stack for debugging
	while (displayStack.size() > 0)
	{
		std::cout << displayStack.top() << " ";
		displayStack.pop();
	}
	std::cout << std::endl;
}

/***********************************************************************
 * Function: isSameStack()
 * Inputs: 2 stacks of strings
 * Summary: Checks if two stacks are exactly the same
 * Based on https://www.geeksforgeeks.org/check-if-the-two-given-stacks-are-same/
 **********************************************************************/
bool isSameStack(
	std::stack<std::string> input, 
	std::stack<std::string> path)
{
	// If the stacks are not the same size
	if (input.size() != path.size())
	{
		// Return false
		return false;
	}

	// Until the stacks are not empty, compare top of both stacks 
    while (input.empty() == false)
	{ 
        // If the top elements of both stacks are the same 
        if (input.top() == path.top())
		{ 
            // Pop top of both stacks 
            input.pop(); 
            path.pop(); 
        } 
        else
		{ 
			// Otherwise return false
            return false;
        } 
    } 

	// If the program gets to this point, then the stacks are the same
	return true;
}

/***********************************************************************
* Function: canonicalization()
* Inputs: String stringPath
 **********************************************************************/
std::stack<std::string> canonicalization(std::string stringPath)
{
	std::stack<std::string> parsedPath;

	for (int i=0; i <= stringPath.size();)
	{
		// Extract one word at a time
		std::string word = "";
		bool endOfWord = false;
		while(!(stringPath[i] == '/' || stringPath[i] == '\\') && i <= stringPath.size())
		{
			word += stringPath[i];
			i++;
		}

		if (word != "")
		{
			// Make the word lowercase
			word = toLowerCase(word);

			if (word == ".")
			{
				// Do nothing
			}
			else if (word == "..")
			{
				// Pop last word off the stack
				if (parsedPath.size() != 0)
					parsedPath.pop();
			}
			else if (word == "...")
			{
				// Pop last two words off the stack
				if (parsedPath.size() != 0)
					parsedPath.pop();
				if (parsedPath.size() != 0)
					parsedPath.pop();
			}
			else if (word == "~")
			{
				// TODO: Empty whole stack?
			}
			else
			{
				// Push word onto stack
				parsedPath.push(word);
			}
		}

		// Skip the slashes to begin the next word
		while (i <= stringPath.size() && (stringPath[i] == '/' || stringPath[i] == '\\'))
		{
			i++;
		}
	}

	return parsedPath;
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
   std::string fullPath(userInput);

   // expand the ~ into user's home directory
   if (userInput[0] == '~')
   {
      // TODO get home directory
   }
   // if userInput is a relative path, append the working directory
   else if (userInput[0] != '/')
   {
      getCurrentDirectory(cwd);
      fullPath += (std::string)cwd;
   }
   // else: do nothing, fullPath already contains the full path

   std::stack<std::string> parsedInput = canonicalization(std::string(fullPath));
   std::stack<std::string> parsedPath = canonicalization(forbiddenPath);

   /*Testing output of userinput into list*/
   std::cout << "..........Output from list: .......................\n";
   std::list<std::string>::iterator itt = parsedUserInput.begin();
   for(; itt != parsedUserInput.end(); itt++)
      std::cout << *itt << " \n";

    // /*Forbidden file path..*/
    // std::cout << "Forbidden file path " << forbiddenPath << "\n";

	
	// Print off stack for debugging
	printStack(parsedInput);
	printStack(parsedPath);

    //check if input against homoHomograph and non-Homograph function
	bool isHomograph = isSameStack(parsedInput, parsedPath);

   return 0;

}
