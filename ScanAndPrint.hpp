

void file_print_solvs(CoefsAndRoots abcx1x2, FILE *fp);

void file_print_coefs(CoefsAndRoots abcx1x2, FILE *fp);

void file_output_AI(CoefsAndRoots abcx1x2, FILE *fpWrite);
/**
	It reads keyboard input and stores it in "Letter" until it reads one of the letters corresponding to a transition to another program state.
     It accepts two such letters as arguments.
 */
void scan_letter(char Previous, char Next, char *Letter);
/**
	\brief reads and returns a positive integer
    reads keyboard input until it reads a positive integer or a letter corresponding to a transition of the program to another state
 */
unsigned int scan_number(states PreviousStep, states *Stepnumber);
/**
	\brief reads the file name from the keyboard
    If a letter is entered instead of a file name, indicating a transition to another state, the name of this state is written in "StateName".
    "PreviousStep" - the previous state to which the program returns when "Q" is pressed
 */
void scan_file_name(char *FileName, states PreviousStep, states *StateName);
/**
	\brief reads the coefficients from the keyboard and writes them into a structure
    If "Q" is entered, "PreviousState" is written to "StateName".
 */
void scan_coeffs(CoefsAndRoots *abcx1x2, states *StateName, states PreviousStep);

void standart_output_AI(CoefsAndRoots abcx1x2);

void standart_print_coefs(CoefsAndRoots abcx1x2);

void standart_print_solves(CoefsAndRoots abcx1x2);
