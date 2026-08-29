#include "kvadratka.hpp"

#include "ScanAndPrint.cpp"


int main()
{
    states StateName = FirstStep;

    FILE *fpWrite = NULL;
    FILE *fpRead = NULL;


    while (StateName != FinishProgramm)
    {
        switch (StateName)
        {
           case FirstStep:   //input
           {

                select_test_or_use(&StateName);
                break;
           }
           case SelectTestMode:
           {
               select_test_mode(&StateName);
               break;
           }
           case AutoTest:
           {
               do_auto_test(&StateName);
               break;
           }
           case TestManually:
           {
               do_manually_test(&StateName);
               break;
           }
           case SelectInputMode:
           {
               select_input_mode(&StateName, &fpRead);
               break;
           }
           case EnterInputFileName:
           {
                enter_input_file_name(&StateName, &fpRead);
                break;
           }
           case SelectOutputMode:
           {
                select_output_mode(&StateName, &fpWrite);
                break;
           }
           case EnterOutputFileName:
           {
                enter_output_file_name(&StateName, &fpWrite);
                break;
           }
           case Work:
           {
               solve_equation(&StateName, &fpRead, &fpWrite);
               break;
           }
           case FinishProgramm:
                break;
           default:
            printf(bold red"Следующий шаг не определён\n"std);
        }
    }
    if(fpRead != NULL)
    {
        fclose(fpRead);
        fpRead = NULL;
    }
    if(fpWrite != NULL)
    {
        fclose(fpWrite);
        fpWrite = NULL;
    }

    printf(bold"Спасибо за то, что воспользовался этой программой\n"std);
}
/*
states next_state_logic(states PreviousStateName, states FistPathSymNumber, states SecondPathSymNumber, char FistPathSym, char SecondPathSym, char Letter)
{
    switch (Letter)
    {
        case FistPathSym:
        {
            return FistPathSymNumber;
        }
        case SecondPathSym:
        {
            return SecondPathSymNumber;
        }
        case 'Q':
        {
            return PreviousStateName;
        }
        case 'E':
        {
            return FinishProgramm;
        }
        default:
            printf("Error next state\n");
    }
}
*/

void clean_buf()
{
	while(getchar() != '\n');
}


void prompt_to_enter_input_mode()
{
    printf(bold"Выбери откуда подавать коэффициенты и введи соответствущую букву\n"std);
	printf(yellow"С клавиатуры   S\n\n"std);
	printf(green"Из файла       F\n\n"std);
	printf(purple"Назад               Q\n"std);
	printf(blue"Завершить программу E\n"std);
}

void prompt_to_exit_or_back()
{
    printf(purple"Назад               Q\n"std);
    printf(blue"Завершить программу E\n"std);
}

void prompt_to_enter_output_mode()
{
    printf(bold"Выбери куда подавать результат и введи соответствущую букву\n"std);
	printf(yellow"На монитор   S\n\n"std);
	printf(green"В файл       F\n\n"std);
	printf(purple"Назад               Q\n"std);
	printf(blue"Завершить программу E\n"std);
}

void prompt_for_standart_input(FILE *fpWrite)
{
	printf(bold"Введи коэффициенты a, b и c\n"std);

	if (fpWrite != NULL)
	{
		printf(purple"Сохранить и назад   Q\n"std);
	}
	else
	{
		printf(purple"Назад               Q\n"std);
	}
	printf(blue"Завершить программу E\n"std);
}

void solve_kvadratka_AI(CoefsAndRoots *equation)
{
	double a = equation->a, b = equation->b, c = equation->c;

	equation->NumberOfRoots = vid_AI(*equation);

	switch (equation->NumberOfRoots)
	{
		case Linear:
		{
			equation->x1 = -c / b;
            if (isinf(equation->x1))
                printf(bold red"Переполнение в х1\n"std);
			break;
		}
		case Descr0:
		{
			equation->x1 = -b / (2 * a);
            if (isinf(equation->x1))
                printf(bold red"Переполнение в х1\n"std);
			break;
		}
		case TwoRoots:
		{
			double sqD = sqrt(b * b - 4 * a * c);
            if (isinf(sqD))
                printf(bold red"Переполнение в дескриминанте\n"std);

			equation->x1 = (-b - sqD) / (2 * a);
            if (isinf(equation->x1))
                printf(bold red"Переполнение в х1\n"std);

			equation->x2 = (-b + sqD) / (2 * a);
            if (isinf(equation->x2))
                printf(bold red"Переполнение в х2\n"std);
			break;
		}
		default: return;
	}
}

vid vid_AI(CoefsAndRoots equation)
{
    if (equation.a == 0 && equation.b == 0 && equation.c == 0)
		return InfRoots;

	else if (equation.a == 0 && equation.b == 0)
		return NoRoots;

	else if (equation.a == 0)
		return Linear;

	double d = equation.b*equation.b - 4*equation.a*equation.c;

	if (d > eps)
		return TwoRoots;

	else if (d < -eps)
		return NoRoots;

	else
		return Descr0;
}

int do_test(CoefsAndRoots refs, CoefsAndRoots rezults)
{
    if (refs.NumberOfRoots != rezults.NumberOfRoots){
        printerror(refs, rezults);
        return 1;
    }
    if ((refs.NumberOfRoots == Linear || refs.NumberOfRoots == Descr0) && !sravndoubl(refs.x1, rezults.x1)){
        printerror(refs, rezults);
        return 1;
    }
    if(((!sravndoubl(refs.x1, rezults.x1)) || (!sravndoubl(refs.x2, rezults.x2) >eps)) && ((!sravndoubl(refs.x2, rezults.x1)) || (!sravndoubl(refs.x1, rezults.x2)))){
        printerror(refs, rezults);
        return 1;
    }
    return 0;
}

void printerror(CoefsAndRoots refs, CoefsAndRoots rezults)
{
    printf("a=%lg b =%lg c=%lg\n", refs.a, refs.b, refs.c);

    printf("Должно быть: ");
    standart_output_AI(refs);

    printf("На выходе:   ");
    standart_output_AI(rezults);
}

double rundomdouble()
{
return 0,1 *rand();
}

void select_test_or_use(states *StateName)
{
    printf("Введите "yellow"T"std" для тестирования и"green" U"std" для использования\nДля выхода введи "red"Q\n"std);

    char Letter = 0;
    scan_letter('T', 'U', &Letter);

    switch (Letter)
    {
        case 'T':
        {
            *StateName = SelectTestMode;
            break;
        }
        case 'U':
        {
            *StateName = SelectInputMode;
            break;
        }
        case 'Q':
        case 'E':
        {
            *StateName = FinishProgramm;
            break;
        }
        default:
            printf("Error next state in select_test_or_use\n");
    }
}

void select_test_mode(states *StateName)
{
    printf(bold"Для автотеста введи "std yellow"A"std bold"\nДля использования своего файла введи"green"M\n"std bold"Назад               "purple"Q\n"std);
    printf(blue"Завершить программу E\n"std);

    char Letter = 0;
    scan_letter('A', 'M', &Letter);

    switch (Letter)
    {
        case 'A':
        {
            *StateName = AutoTest;
            break;
        }
        case 'M':
        {
            *StateName = TestManually;
            break;
        }
        case 'Q':
        {
            *StateName = FirstStep;
            break;
        }
        case 'E':
        {
            *StateName = FinishProgramm;
            break;
        }
        default:
            printf("Error next state in select_test_mode\n");
    }
}

void do_auto_test(states *StateName)
{
    printf(bold"Введите количество тестов\n"std);
    prompt_to_exit_or_back();

    unsigned int NumberOfTests = 0;
    NumberOfTests = scan_number(SelectTestMode, StateName);

    for(int i=0; i < NumberOfTests; i++)
    {
        CoefsAndRoots refs = {.a  = rundomdouble(), .b = 0, .c = 0, .NumberOfRoots = TwoRoots, .x1 = rundomdouble(), .x2 = rundomdouble(),};
        refs.b  = -refs.a * (refs.x1 + refs.x2);
        refs.c  = refs.a * refs.x1 * refs.x2;
        CoefsAndRoots rezults = {.a = refs.a, .b = refs.b, .c = refs.c, .NumberOfRoots = Unknown, .x1 = 0, .x2 = 0};


        solve_kvadratka_AI(&rezults);

        do_test(refs, rezults);
    }
    printf(bold"тест завершён\n"std);

    *StateName = FirstStep;
}

void do_manually_test(states *StateName)
{
    printf(bold"Введите количество тестов\n"std);
    prompt_to_exit_or_back();
    FILE *fpRead = NULL;

    unsigned int NumberOfTests = 0;
    NumberOfTests = scan_number(SelectTestMode, StateName);

    if (*StateName != TestManually)
        return;

    printf(bold"Введите название тестового файла\n"std);
    prompt_to_exit_or_back();

    char FileName[20] = {};
    scan_file_name(FileName, TestManually, StateName);
    while ((fpRead = fopen(FileName, "r")) == NULL && *StateName == TestManually)
    {
        if (*StateName == FirstStep)
        {
            *StateName = TestManually;
            break;
        }
        if ((fpRead = fopen(FileName, "r")) == NULL)
            printf("Файл %s не открывается\n", FileName);

        scan_file_name(FileName, SelectTestMode, StateName);
    }
    if (*StateName == TestManually)
    {
        CoefsAndRoots refs[NumberOfTests] = {};
        CoefsAndRoots rezults = {};

        for (int i = 0; i < NumberOfTests; i++)
        {
            if (fscanf(fpRead, "%lg%lg%lg%d%lg%lg", &refs[i].a, &refs[i].b, &refs[i].c, &refs[i].NumberOfRoots, &refs[i].x1, &refs[i].x2) != 6)
            {
                printf("Ой! Что-то пошло не так\n");
                *StateName = FirstStep;
                break;
            }
            solve_kvadratka_AI(&rezults);

            do_test(refs[i], rezults);
        }
    }
    if (fpRead != NULL)
    {
        fclose(fpRead);
        fpRead = NULL;
    }
    if (*StateName == TestManually)
    {
    printf("тест завершён\n");
    *StateName = FirstStep;
    }
    else
        *StateName = TestManually;
}

void select_input_mode(states *StateName, FILE **fpRead)
{
    prompt_to_enter_input_mode();

    if (*fpRead != NULL)
    {
        fclose(*fpRead);
        *fpRead = NULL;
    }

    char Letter = 0;
    scan_letter('S', 'F', &Letter);

    switch (Letter)
    {
        case 'S':
        {
            *StateName = SelectOutputMode;
            break;
        }
        case 'F':
        {
            *StateName = EnterInputFileName;
            break;
        }
        case 'Q':
        {
            *StateName = FirstStep;
            break;
        }
        case 'E':
        {
            *StateName = FinishProgramm;
            break;
        }
        default:
            printf("Error next state\n");
    }
}

void enter_input_file_name(states *StateName, FILE **fpRead)
{
    char FileName[FileNameLenght] = {};
    assert(*StateName == EnterInputFileName);
    if(*fpRead != NULL)
    {
        fclose(*fpRead);
        *fpRead = NULL;
    }
    while (*fpRead == NULL && *StateName == EnterInputFileName)
    {
        printf(bold"Введите имя файла с коэффициентами\n"std);
        prompt_to_exit_or_back();

        scan_file_name(FileName, SelectInputMode, StateName);
        assert(*StateName == SelectInputMode || *StateName == EnterInputFileName);
        if(*StateName == EnterInputFileName)
            if ((*fpRead = fopen(FileName, "r")) == NULL)
                printf(bold red"Файл %s не открылся\n"std, FileName);
    }
    if(*StateName != EnterInputFileName && *fpRead != NULL)
    {
        fclose(*fpRead);
        *fpRead = NULL;
    }
    assert(*StateName == EnterInputFileName || *fpRead == NULL);
    if(*StateName == EnterInputFileName)
        *StateName = SelectOutputMode;
}

void select_output_mode(states *StateName, FILE **fpWrite)
{
    prompt_to_enter_output_mode();

    if (*fpWrite != NULL)
    {
        fclose(*fpWrite);
        *fpWrite = NULL;
    }

    char Letter = 0;
    scan_letter('S', 'F', &Letter);

    if (*fpWrite == NULL)
    {
        switch (Letter)
        {
            case 'S':
            {
                *StateName = Work;
                break;
            }
            case 'F':
            {
                *StateName = EnterOutputFileName;
                break;
            }
            case 'Q':
            {
                *StateName = SelectInputMode;
                break;
            }
            case 'E':
            {
                *StateName = FinishProgramm;
                break;
            }
            default:
                printf("Error next state\n");
        }
    }
    else
    {
        switch (Letter)
        {
            case 'S':
            {
                *StateName = Work;
                break;
            }
            case 'F':
            {
                *StateName = EnterOutputFileName;
                break;
            }
            case 'Q':
            {
                *StateName = EnterInputFileName;
                break;
            }
            case 'E':
            {
                *StateName = FinishProgramm;
                break;
            }
            default:
                printf("Error next state\n");
        }
    }
}

void enter_output_file_name(states *StateName, FILE **fpWrite)
{
    char FileName[FileNameLenght] = {};
    while (*fpWrite == NULL && *StateName == EnterOutputFileName)
    {
        printf(bold"Введите имя файла назначения\n"std);
        prompt_to_exit_or_back();

        scan_file_name(FileName, SelectOutputMode, StateName);
        if(*StateName != EnterOutputFileName)
            return;

        if ((*fpWrite = fopen(FileName, "w")) == NULL)
            printf(bold red"Файл %s не открылся\n"std, FileName);
    }
    *StateName = Work;
}

void solve_equation(states *StateName, FILE **fpRead, FILE **fpWrite)
{
    CoefsAndRoots equation = {};
    while (*StateName == Work)
    {
        if (*fpRead != NULL)
        {
            while(fscanf(*fpRead, "%lg%lg%lg", &equation.a, &equation.b, &equation.c) == 3)
            {
                if (!(isinf(equation.a) || isinf(equation.b)|| isinf(equation.c)))
                {
                    solve_kvadratka_AI(&equation);

                    if (*fpWrite == NULL)
                    {
                        standart_output_AI(equation);
                    }
                    else
                    {
                        file_output_AI(equation, *fpWrite);
                    }
                }
                else
                    printf(bold red"Хорошая попытка ;)\n"std);
            }
            printf("Готово\n");
            *StateName = FirstStep;
        }

        else
        {
            while (*StateName == Work)
            {
                prompt_for_standart_input(*fpWrite);

                scan_coeffs(&equation, StateName, FirstStep);
                if (*StateName == Work)
                {
                    solve_kvadratka_AI(&equation);

                    if (*fpWrite == NULL)
                    {
                        standart_output_AI(equation);
                    }
                    else
                    {
                        file_output_AI(equation, *fpWrite);
                    }
                }
            }
            if (*fpWrite != NULL)
            {
                fclose(*fpWrite);
                *fpWrite = NULL;
            }
        }
    }
}

int sravndoubl(double a, double b){
    double biggest =0;
    double moda =fabs(a), modb =fabs(b);
    if(fabs(a)>fabs(b))
        biggest =moda;
    else
        biggest =modb;
    if(fabs(a-b)<biggest*0.001){          //если a==b вернёт 1
        return 1;
    }
    else
        return 0;
}
