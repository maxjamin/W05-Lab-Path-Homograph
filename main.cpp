#include <iostream>
#include <unistd.h>
#include <list>
#include <stack>
#include <cstring>
#include <string>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#define MaxNum 1000
#define	forbiddenPath "/home/readyone/Documents/school2/schoolWinter2020/cs470/W05-Lab-Path-Homograph"

using namespace std;

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
	stack<string> input, 
	stack<string> path)
{
	// If the stacks are not the same size
	if (input.size() != path.size())
	{
		/*cout << "Size s1 = " << input.size() << "; size s2 = " << path.size() << '\n';

		while (!(input.empty() && path.empty()))
		{
			if (!input.empty())
			{
				cout << "Input: " << input.top() << '\n';
				input.pop();
			}
			if (!path.empty())
			{
				cout << "Path: " << path.top() << '\n';
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
string getUserInput()
{
  string userInput;
  cout << "Please enter a filepath: ";
  cin>> userInput;
  return userInput;
}

/***********************************************************************
* Function: getHomedir
* Inputs: None
* Summary: get the home directory in a char array. Based from:
https://cboard.cprogramming.com/c-programming/164689-how-get-users-home-directory.html
 **********************************************************************/
char *getHomedir()
{
    char homedir[MAX_PATH];
    #ifdef _WIN32
        // For running this program on Windows machines
        snprintf(homedir, MAX_PATH, "%s%s", getenv("HOMEDRIVE"), getenv("HOMEPATH"));
    #else
        // For running this program on Linux machines
        snprintf(homedir, MAX_PATH, "%s", getenv("HOME"));
    #endif
        return strdup(homedir);
}

/***********************************************************************
* Function: getCurrentDirectory
* Inputs: char array by reference
* Summary: get current directory in a char array. Based from:
https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
 **********************************************************************/
string getCurrentDirectory()
{
    char cwd[MaxNum];
	//cout << "test01\n";
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
    	// printf("Current working dir: %s\n", cwd);
   	} else {
       	perror("getcwd() error");
       	return "";
   	}
  	return string(cwd);
} 

/***********************************************************************
* Function: toLowerCase()
* Inputs: string 
* Summary: Converts a string to all lowercase values
 Based on https://stackoverflow.com/questions/313970/how-to-convert-stdstring-to-lower-case
 **********************************************************************/
string toLowerCase(string input)
{
  	//replace Uppercase with lowerCase
  	transform(input.begin(), input.end(), input.begin(),
    [](unsigned char c){ return tolower(c); });
	
	return input;
}

/***********************************************************************
* Function: printStack()
* Inputs: stack of strings 
* Summary: prints the contents of the stack
 **********************************************************************/
void printStack(stack<string> stackToDisplay)
{
  	stack<string> displayStack;
	while (stackToDisplay.size() > 0)
	{
		displayStack.push(stackToDisplay.top());
		stackToDisplay.pop();
	}

	// Print off stack for debugging
	while (displayStack.size() > 0)
	{
		if (displayStack.top() == "")
			cout << "- ";

		else if (displayStack.top() == " ")
			cout << ". ";
		else
			cout << displayStack.top() << " ";
		displayStack.pop();
	}
	cout << endl;
}

/***********************************************************************
* Function: canonicalization()
* Inputs: String stringPath
 **********************************************************************/
stack<string> canonicalization(string stringPath)
{
	stack<string> parsedPath;

	if (stringPath[0] == '/')
	{
		// This is an absolute path.
		// The stringPath contains the entire filepath to check
        // So, add nothing to the front
	}
	else if (stringPath[0] == '~')
	{
		// This is a relative path starting from the user's HOME directory.
		// Paste the HOME directory in before the stringPath
        string homedir = getHomedir();
        // cout << "Home Directory: " << homedir << endl;
        stringPath = homedir + stringPath;
	}
	else
	{
		// This is a relative path starting from the current working directory.
		// Paste that in front of the stringPath
        string cwd = getCurrentDirectory();
        stringPath = cwd + stringPath;
	}

	for (int i=0; i <= stringPath.size();)
	{
		// Extract one word at a time
		string word = "";
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
				// This should only do something when it is at the beginning
                // So, we will do nothing here :)
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
    cout << "Homograph Test\n\n";

    string testString = "test/././filepathtest/testing/";
    string testAgainst = "test/filepathtest/testing/";
    //Test . handling .. handling ... handling ~ handling

    cout << "Test 1\nVerify that cannonicalization can handle filepaths with \"./\"\n";
    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    stack<string> c1 = canonicalization(testString);
    stack<string> c2 = canonicalization(testAgainst);
    if(isSameStack(c1,c2))
        cout << "\tCannonicalization test Success\n\n";
    else{
        cout << "\tCannonicalization test Failure\n\n";
        return ;
    }

	printStack(c2);

    cout << "Test 2\nVerify that cannonicalization can handle filepaths with \"../\"\n";
    testString = "test/filepathtest/../filepathtest/testing";

    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    c1 = canonicalization(testString);
    if(isSameStack(c1,c2))
        cout << "\tCannonicalization test A Success\n\n";
    else{
        cout << "\tCannonicalization test A Failure\n\n";
        return ;
    }

    testString = "../../../test/filepathtest/testing/";

    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    c1 = canonicalization(testString);

    if(isSameStack(c1,c2))
        cout << "\tCannonicalization test B Success\n\n";
    else{
        cout << "\tCannonicalization test B Failure\n\n";
        return ;
    }

    cout << "Test 3\nVerify that cannonicalization can handle filepaths with \".../\"\n";
    testString = "test/filepathtest/.../test/filepathtest/testing";

    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    c1 = canonicalization(testString);
    if(isSameStack(c1,c2))
        cout << "\tCannonicalization test A Success\n\n";
    else{
        cout << "\tCannonicalization test A Failure\n\n";
        return ;
    }

    testString = "test/.../test/filepathtest/testing/";

    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    c1 = canonicalization(testString);
    if(isSameStack(c1,c2))
        cout << "\tCannonicalization test B Success\n\n";
    else{
        cout << "\tCannonicalization test B Failure\n\n";
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
    cout << "Non-Homograph Test\n\n";

    // cout << "Test 1\nVerify that user input is accepted\n";
    // string testString = getUserInput();

    // if(testString.length() != 0)
    // cout << "Successfully grabbed user input\n";

    cout << "Test 2\nEnsure that isSameStack functions properly\n";
    stack<string> testStack1;
    stack<string> testStack2;
    stack<string> testStack3;
    testStack1.push("1");
    testStack1.push("2");
    testStack1.push("3");
    testStack2.push("1");
    testStack2.push("2");
    testStack2.push("3");
    testStack3.push("a");
    testStack3.push("b");
    testStack3.push("c");

    if(isSameStack(testStack1,testStack2) && !isSameStack(testStack1,testStack3))
        cout << "\tSuccess - isSameStack is functioning properly. Canon can be compared.\n\n";
    else{
        cout << "\tFailure. isSameStack can not compare stack Canons.\n\n";
        return;
    }

    string testString = "test/notsamepathtest/testing/";
    string testAgainst = "test/filepathtest/testing/";

    stack<string> c1 = canonicalization(testString);
    stack<string> c2 = canonicalization(testAgainst);

    cout << "Test 3\nVerify that cannonicalization can recognize ";
    cout << "when paths are not homographs\n";
    cout << "\t" << testString << "\n\t" << testAgainst << endl;
    if(!isSameStack(c1,c2))
        cout << "\tCannonicalization test Success - non homograph\n\n";
    else{
        cout << "\tCannonicalization test Failure\n\n";
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
    HomographsTest();
    NonHomographsTest();

    return 0;
}
