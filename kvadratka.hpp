#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FileNameLenght 20
#define eps 0.001
#define std "\033[0m"
#define black "\033[30m"
#define red "\033[31m"
#define green "\033[32m"
#define yellow "\033[33m"
#define blue "\033[34m"
#define purple "\033[35m"
#define white "\033[37m"
#define bold "\033[1m"

/**
	\brief Each name corresponds to the state of the program.
	The navigation variable "StateName" takes one of these values ​​to determine the program's next state.
 */
enum states
{   ///finish thr programm
	FinishProgramm = 0,
	///initial menu
    FirstStep = 1,
	///allows you to select the source of the equation coefficients
    SelectTestMode = 2,
	///do automatic tast
    AutoTest = 3,
	///allows you to select the source of the equation coefficients
    TestManually = 4,
	///runs a test from a user-owned file
    SelectInputMode = 5,
	///if the equation coefficients are derived from a file, it prompts for the filename
    EnterInputFileName = 6,
	///it offers a choice of where to output the result
    SelectOutputMode = 7,
	///if the result is written to a file, it prompts for the filename
    EnterOutputFileName = 8,
	///solves the equations
    Work = 9
};
/**
	\brief Each name corresponds to the type or number of solutions to the equation.
 */
enum vid
{	 ///if equation is linear
	Linear = 10,
	///if descriminant = 0
	Descr0 = 11,
	///if no roots
	NoRoots = 0,
	///if 2 roots
	TwoRoots = 2,
	///infinitely many roots
	InfRoots = 3,
	///The program was unable to correctly process the entered coefficients
	Unknown = 4
};

enum WorR {
	write,
	read
};

///stores coefficients, solutions, and the number of roots.
struct CoefsAndRoots
{
	double a;
	double b;
	double c;
	vid NumberOfRoots;
	double x1;
	double x2;
};

///returns 1 if the numbers differ by less than 0.001
int sravndoubl(double a, double b);
/**
	\brief Reads the coefficients, solves the equation, and outputs the result
	If stream 1 is open, it reads the coefficients from that file;
	otherwise, it reads them from the keyboard. If stream 2 is open, it writes the result to that file;
	otherwise,it displays the result on the monitor. Upon completion, it returns the user to the initial stage.
 */
void solve_equation(states *StateName, FILE **fpRead, FILE **fpWrite);
/**
	\brief prompts you to enter the name of the file where the solutions will be saved
	Once reading is complete, a write stream is opened. You can return to the output format selection stage or terminate the program.
 */
void enter_output_file_name(states *StateName, FILE **fpWrite);
/**
	\brief offers a choice of output format for solutions
	Closes the read stream if it is open. It is possible to step back.
*/
void select_output_mode(states *StateName, FILE **fpWrite);
/**
	\brief prompts you to enter the name of the file from which to take the coefficients
	After reading, it opens the stream. It is possible to return to the input format selection state or terminate the program.
 */
void enter_input_file_name(states *StateName, FILE **fpRead);
/**
	\brief offers a choice of input format
	Closes the read stream if it is open.You can choose to enter the coefficients from a file or via the keyboard. You can return to the initial state or exit the program.
 */
void select_input_mode(states *StateName, FILE **fpRead);
/**
	\brief takes the name of your test file and runs the tests
 */
void do_manually_test(states *StateName);
/**
	\brief performs automatic testing
 */
void do_auto_test(states *StateName);
/**
	\brief invites you to choose the test format (automatic or from your own)
 */
void select_test_mode(states *StateName);
/**
	\brief You can choose between testing and usage.
	This is the initial state. The program can be terminated.
 */
void select_test_or_use(states *StateName);
/**
	\brief outputs errors during testing
 */
void printerror(CoefsAndRoots refs, CoefsAndRoots rezults);
/**
	\brief compares the test answers with the answers calculated by the program
 */
int do_test(CoefsAndRoots refs, CoefsAndRoots rezults);
/**
	\brief returns the form of the equation
	takes coefficients a, b, and c as input and determines the type and number of roots
 */
vid vid_AI(CoefsAndRoots abcx1x2);
/**
	\brief solves the equation
	accepts a pointer to a structure containing the coefficients and writes the roots into it
 */
void solve_equation_AI(CoefsAndRoots *abcx1x2);
/**
	\brief invites you to enter the coefficients from the keyboard
	Depending on where the decisions are recorded, the messages will varyable
 */
void prompt_for_standart_input(FILE *fpWrite);
/**
	\brief
 */
void prompt_to_enter_output_mode();
/**
	\brief
 */
void prompt_to_exit_or_back();
/**
	\brief
 */
void prompt_to_enter_input_mode();
/**
	\brief returns a random number of type double
 */
double rundomdouble();
/**
	\brief cleans buffer
 */
void clean_buf();
