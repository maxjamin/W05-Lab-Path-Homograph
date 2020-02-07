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
		/*std::cout << "Size s1 = " << input.size() << "; size s2 = " << path.size() << '\n';

		while (!(input.empty() && path.empty()))
		{
			if (!input.empty())
			{
				std::cout << "Input: " << input.top() << '\n';
				input.pop();
			}
			if (!path.empty())
			{
				std::cout << "Path: " << path.top() << '\n';
				path.pop();
			}
		}*/

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
* Function:
*    getUserInput()
* Inputs: char pointer
* Summary:
*    Get the userinput and pass to parameter. 
 ************************************************************************/
std::string getUserInput()
{
  std::string userInput;
  std::cout << "Please enter a filepath: ";
  std::cin>> userInput;
  return userInput;
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
		if (displayStack.top() == "")
			std::cout << "- ";

		else if (displayStack.top() == " ")
			std::cout << ". ";
		else
			std::cout << displayStack.top() << " ";
		displayStack.pop();
	}
	std::cout << std::endl;
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

		if (word.empty())
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
*    HomographsTest()
* Inputs:nil
* Summary:
*    This function serves as a test case for canonicalization
************************************************************************/
void HomographsTest()
{
    std::cout << "Homograph Test\n\n";

    std::string testString = "test/././filepathtest/testing/";
    std::string testAgainst = "test/filepathtest/testing/";
    //Test . handling .. handling ... handling ~ handling

    std::cout << "Test 1\nVerify that cannonicalization can handle filepaths with \"./\"\n";
    std::cout << testString << std::endl << testAgainst << std::endl;
    std::stack<std::string> c1 = canonicalization(testString);
    std::stack<std::string> c2 = canonicalization(testAgainst);
    if(isSameStack(c1,c2))
        std::cout << "Cannonicalization test Success\n\n";
    else{
        std::cout << "Cannonicalization test Failure\n\n";
        return ;
    }

	printStack(c2);

    std::cout << "Test 2\nVerify that cannonicalization can handle filepaths with \"../\"\n";
    testString = "test/filepathtest/../filepathtest/testing";

    std::cout << testString << std::endl << testAgainst << std::endl;
    c1 = canonicalization(testString);
	printStack(c1);
    if(isSameStack(c1,c2))
        std::cout << "Cannonicalization test A Success\n\n";
    else{
        std::cout << "Cannonicalization test A Failure\n\n";
        return ;
    }

    testString = "../../../test/filepathtest/testing/";

    std::cout << testString << std::endl << testAgainst << std::endl;
    c1 = canonicalization(testString);

	printStack(c1);
    if(isSameStack(c1,c2))
        std::cout << "Cannonicalization test B Success\n\n";
    else{
        std::cout << "Cannonicalization test B Failure\n\n";
        return ;
    }

    std::cout << "Test 3\nVerify that cannonicalization can handle filepaths with \".../\"\n";
    testString = "test/filepathtest/.../test/filepathtest/testing";

    std::cout << testString << std::endl << testAgainst << std::endl;
    c1 = canonicalization(testString);
    if(isSameStack(c1,c2))
        std::cout << "Cannonicalization test A Success\n\n";
    else{
        std::cout << "Cannonicalization test A Failure\n\n";
        return ;
    }

    testString = "test/.../test/filepathtest/testing/";

    std::cout << testString << std::endl << testAgainst << std::endl;
    c1 = canonicalization(testString);
    if(isSameStack(c1,c2))
        std::cout << "Cannonicalization test B Success\n\n";
    else{
        std::cout << "Cannonicalization test B Failure\n\n";
        return ;
    }

    //cout << "Test 4\nVerify that cannonicalization can handle filepaths with \"~/\"\n";

    return ;
}
 
/***********************************************************************
* Function:
*    NonHomographsTest()
* Inputs:
* Summary:
*    These are test cases to make sure that non homographs are not accidentally
*    called homographs by the canonicalization function and tests other functions
************************************************************************/
void NonHomographsTest()
{
    std::cout << "Non-Homograph Test\n\n";

    std::cout << "Test 1\nVerify that user input is accepted\n";
    std::string testString = getUserInput();

    if(testString.length() != 0)
    std::cout << "Successfully grabbed user input\n";

    std::cout << "Test 2\n ensure that isSameStack functions properly\n";
    std::stack<std::string> testStack1;
    std::stack<std::string> testStack2;
    std::stack<std::string> testStack3;
    testStack1.push("1");
    testStack1.push("2");
    testStack1.push("3");
    testStack2.push("1");
    testStack2.push("2");
    testStack2.push("3");
    testStack1.push("a");
    testStack1.push("b");
    testStack1.push("c");

    if(isSameStack(testStack1,testStack2) && !isSameStack(testStack1,testStack3))
        std::cout << "Success - isSameStack is functioning properly. Canon can be compared.\n";
    else{
        std::cout << "Failure. isSameStack can not compare stack Canons.\n";
        return;
    }

    testString = "test/filepath.test/testing/";
    std::string testAgainst = "test/filepathtest/testing/";

    std::cout << "Test 3\nVerify that cannonicalization can recognize";
    std::cout << "when a \".\" is not part of filepath\n";
    std::cout << testString << std::endl << testAgainst << std::endl;
    std::stack<std::string> c1 = canonicalization(testString);
    std::stack<std::string> c2 = canonicalization(testAgainst);
    if(!isSameStack(c1,c2))
        std::cout << "Cannonicalization test Success - non homograph\n\n";
    else{
        std::cout << "Cannonicalization test Failure\n\n";
        return ;
    }

    testString = "test/notsamepathtest/testing/";

    std::cout << "Test 4\nVerify that cannonicalization can recognize";
    std::cout << "when a paths not homographs\n";
    std::cout << testString << std::endl << testAgainst << std::endl;
    c1 = canonicalization(testString);
    c2 = canonicalization(testAgainst);
    if(!isSameStack(c1,c2))
        std::cout << "Cannonicalization test Success - non homograph\n\n";
    else{
        std::cout << "Cannonicalization test Failure\n\n";
        return ;
    }

    return ;
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
//    std::string userInput;
//    char cwd[MaxNum];

//    std::list<std::string> parsedCwd;
//    std::list<std::string> parsedUserInput;

//    //get user input, place into list<String>
//    userInput = getUserInput();
//    std::string fullPath(userInput);

//    // expand the ~ into user's home directory
//    if (userInput[0] == '~')
//    {
//       // TODO get home directory
//    }
//    // if userInput is a relative path, append the working directory
//    else if (userInput[0] != '/')
//    {
//       getCurrentDirectory(cwd);
//       fullPath += (std::string)cwd;
//    }
//    // else: do nothing, fullPath already contains the full path

//    std::stack<std::string> parsedInput = canonicalization(std::string(fullPath));
//    std::stack<std::string> parsedPath = canonicalization(forbiddenPath);

//    /*Testing output of userinput into list*/
//    std::cout << "..........Output from list: .......................\n";
//    std::list<std::string>::iterator itt = parsedUserInput.begin();
//    for(; itt != parsedUserInput.end(); itt++)
//       std::cout << *itt << " \n";

//     // /*Forbidden file path..*/
//     // std::cout << "Forbidden file path " << forbiddenPath << "\n";

	
// 	// Print off stack for debugging
// 	printStack(parsedInput);
// 	printStack(parsedPath);

//     //check if input against homoHomograph and non-Homograph function
// 	bool isHomograph = isSameStack(parsedInput, parsedPath);

    HomographsTest();
    NonHomographsTest();

    return 0;
}
