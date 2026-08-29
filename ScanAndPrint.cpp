void standart_print_solves(CoefsAndRoots equation)
{
	switch(equation.NumberOfRoots)
	{
		case NoRoots:
		{
			printf("Корней нет\n");
			break;
		}
		case Linear:
		case Descr0:
		{
			printf("Корень %lg\n", equation.x1);
			break;
		}
		case TwoRoots:
		{
			printf("x1 = %lg    x2 = %lg\n", equation.x1, equation.x2);
			break;
		}
		case InfRoots:
		{
			printf("Бесконечность корней\n");
			break;
		}
		case Unknown:
			printf("Флаг не установлен\n");
		default: return ;
	}
}

void standart_print_coefs(CoefsAndRoots equation)
{
	printf("%lgx^2 ", equation.a);

	if(equation.b<0)
		printf("- %lgx ", -equation.b);
	else
		printf("+ %lgx ", equation.b);


	if(equation.c<0)
		printf("- %lg ", -equation.c);
	else
		printf("+ %lg ", equation.c);

	printf(" = 0  ");
}

void scan_letter(char Previous, char Next, char *Letter)
{
    scanf(" %c", Letter);
	clean_buf();

	while(*Letter != Previous && *Letter != Next && *Letter != 'Q' && *Letter != 'E')
	{
		printf(bold"Может ты введёшь нужную букву?\n"std);
		scanf(" %c", Letter);
		clean_buf();
	}
}

unsigned int scan_number(states PreviousStep, states *StateName)
{
    unsigned int NumberOfTests = 0;
    while (scanf("%u", &NumberOfTests) != 1)
    {
        char CheckQE = 0;

        scanf(" %c", &CheckQE);
        clean_buf();

        if (CheckQE == 'E')
        {
        *StateName = FinishProgramm;
        return 0;
        }
        if (CheckQE == 'Q')
        {
            *StateName = PreviousStep;
            return 0;
        }
        else
            printf("Введи нормальное число\n");
    }
    return NumberOfTests;
}


void scan_file_name(char *FileName, states PreviousStep, states *StateName)
{
    scanf("%19s", FileName);
	clean_buf();

    if (!strcmp(FileName, "E"))
    {
        *StateName = FinishProgramm;
        return ;
    }
    else if (!strcmp(FileName, "Q"))
    {
        *StateName = PreviousStep;
    }
}

void scan_coeffs(CoefsAndRoots *equation, states *StateName, states PreviousStep)
{
    while (scanf("%lg%lg%lg", &equation->a, &equation->b, &equation->c) != 3 && *StateName == Work)
    {
        char CheckQE = 0;

        scanf(" %c", &CheckQE);
        clean_buf();

        if (CheckQE == 'E')
        {
            *StateName = FinishProgramm;
            break;
        }
        else if (CheckQE == 'Q')
        {
            *StateName = PreviousStep;
            break;
        }
        else
            printf("Введи нормальное число\n");
    }
    if (isnan(equation->a) || isnan(equation->b)|| isnan(equation->c))
    {
        equation->a = 0;
        equation->b = 0;
        equation->c = 0;
        printf(bold red"Хорошая попытка ;)\n"std);
    }
}

void file_print_coefs(CoefsAndRoots equation, FILE *fp)
{
	fprintf(fp, "%lgx^2 ", equation.a);
	if(equation.b<0)
		fprintf(fp, "- %lgx ", -equation.b);
	else
		fprintf(fp, "+ %lgx ", equation.b);
	if(equation.c<0)
		fprintf(fp, "- %lg ", -equation.c);
	else
		fprintf(fp, "+ %lg ", equation.c);
	fprintf(fp, " = 0  ");
}

void file_print_solvs(CoefsAndRoots equation, FILE *fp)
{
	switch(equation.NumberOfRoots){
		case NoRoots:{
			fprintf(fp, "Корней нет\n");
			break;
			}
		case Linear:
		case Descr0:{
			fprintf(fp, "Корень %lg\n", equation.x1);
			break;
			}
		case TwoRoots:{
			fprintf(fp, "x1 = %lg    x2 = %lg\n", equation.x1, equation.x2);
			break;
			}
		case InfRoots:{
			fprintf(fp, "Бесконечность корней\n");
			break;
			}
		case Unknown:
			fprintf(fp, red"Флаг не установлен\n"std);
		default: return;
	}
}

void file_output_AI(CoefsAndRoots equation, FILE *fpWrite)
{
	printf("Думаю\n");

	file_print_coefs(equation, fpWrite);

	file_print_solvs(equation, fpWrite);
}

void standart_output_AI(CoefsAndRoots equation)
{
	standart_print_coefs(equation);

	standart_print_solves(equation);
}




