/**
 * @file CSC450_Mod3_CT_Mossberg.cpp
 * @Console program that stores three integers and copies each to the heap.
 *
 * Prompts the user for three integer values, stores each in a stack variable,
 * allocates a matching int with new, prints the stack value, pointer address,
 * and pointed-to value, then releases each allocation with delete.
 *
 * @author Benjamin Mossberg
 * @date 2026-10-01
 * @version 1.0
 */

#include <iostream>
#include <limits>
#include <cstdlib>

using std::cout;
using std::endl;

/**
 * @brief Reads one integer from standard input.
 *
 * On failure the stream is cleared and the rest of the line is discarded so a
 * later read is not stuck on the same token.
 *
 * @param label Prompt written before the read.
 * @param out   Variable that receives the value on success.
 * @return true if an integer was extracted; false on EOF or a non-integer token.
 */
bool readInt(const char* label, int& out)
{
	cout << label;	// Prompt; no read yet
	if (!(std::cin >> out))	// False on EOF or non-integer token
	{
		std::cin.clear();	// Drop fail bit to allow later read
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// Discard remainder of line
return false;	// Out unchanged
}
return true;	// Out holds extracted integer
}

/**
 * @brief Prints a stack integer and the heap integer it was copied into.
 *
 * Pass-by-value of variables used to create copies and preserve original variables
 *
 * @param name  Label for the variable.
 * @param value Stack value.
 * @param ptr   Non-null pointer to the heap copy. Caller owns ptr.
 */
void show(const char* name, int value, const int* ptr)
{
	cout << name << " variable = " << value
			<< ", pointer address = " << ptr
			<< ", pointed-to value = " << *ptr << endl;
}

/**
 * @brief Reads three integers, copies each to dynamic memory, and prints both.
 *
 * Allocation uses new. Every successful allocation is released with delete.
 * A failed read exits before any allocation. A failed allocation deletes any
 * pointer already obtained and exits.
 *
 * @return 0 on success; 1 if input or allocation fails.
 */
int main()
{
	int a = 0;
	int b = 0;
    int c = 0;

    if (!readInt("Enter first integer: ", a) ||
    		!readInt("Enter second integer: ", b) ||
			!readInt("Enter third integer: ", c))
    {
        std::cerr << "Input was not a valid integer. No heap allocation performed."
        		<< endl;
        system("pause");
        return 1;
    }


    int* pa = nullptr;
    int* pb = nullptr;
    int* pc = nullptr;

    try
    {
    	// Throws std::bad_alloc on failure
    	pa = new int(a);
    	pb = new int(b);
    	pc = new int(c);
    }

    catch (const std::bad_alloc& ex)
    {
    	// Release resources on failure path
    	delete pa;
    	delete pb;
    	delete pc;
    	std::cerr << "Allocation failed: " << ex.what() << endl;
    	system("pause");
    	return 1;
    }

    cout << "Stack variables and heap copies:" << endl;
    show("a", a, pa);
    show("b", b, pb);
    show("c", c, pc);

    // Release resources on success path
    delete pa;
    delete pb;
    delete pc;
    pa = nullptr;
    pb = nullptr;
    pc = nullptr;

    system("pause");
    return 0;
}
