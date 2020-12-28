#include "postfix.h"
#include "stack.h"


string TPostfix::ToPostfix()
{
	TStack<char> StackOper(LenInf); //стэк операций
	postfix = "";
	for (int i = 0; i < LenInf; i++) //(a*b+c)   ab*c+
	{
		if (infix[i] == '(') StackOper.Put(infix[i]);
		else if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/'))
		{
			if (StackOper.IsEmpty())
				StackOper.Put(infix[i]);

			else if (Priority(StackOper.GetTop()) == Priority(infix[i]))
			{
				postfix += StackOper.Get();
				StackOper.Put(infix[i]);
			}
			else if (Priority(StackOper.GetTop()) < Priority(infix[i]))
			{
				StackOper.Put(infix[i]);
			}
			else
			{
				if ((Priority(StackOper.GetTop()) > Priority(infix[i])))
				{
					while ((!StackOper.IsEmpty()))
					{
						postfix += StackOper.Get();
					}
					StackOper.Put(infix[i]);

				}

			}
		}
		else if (infix[i] == ')')
		{
			while ((!StackOper.IsEmpty()) && (StackOper.GetTop() != '('))
			{
				postfix += StackOper.Get();
			}
			StackOper.Get();
		}
		else
		{
			postfix += infix[i];
		}
	}
	while (!StackOper.IsEmpty())
	{
		postfix += StackOper.Get();
	}
	return postfix;
}

double TPostfix::Calculate(double* _MasValue)
{
	int var = GetInfixVar();
	TStack<double> Val(var);

	double* ValVAr = new double[var];
	for (int i = 0; i < var; i++) ValVAr[i] = _MasValue[i];
	double val1, val2;
	int j = 0;
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isalpha(postfix[i]))
		{
			Val.Put(ValVAr[j++]);
		}
		else
		{
			val1 = Val.Get();
			val2 = Val.Get();

			switch (postfix[i])
			{
			case '+':
				Val.Put(val1 + val2);
				break;
			case '-':
				Val.Put(val2 - val1);
				break;
			case '/':
				Val.Put(val2 / val1);
				break;
			case '*':
				Val.Put(val1 * val2);
				break;
			}
		}
	}
	return Val.GetTop();
}

int TPostfix::Priority(char elem)
{
	if (elem == '(')
		return 0;
	else if (elem == ')')
		return 1;
	else if (elem == '+' || elem == '-')
		return 2;
	else if (elem == '*' || elem == '/')
		return 3;

	else throw ("Erorr");
}

int TPostfix::GetLen()
{
	return infix.length();
}

int TPostfix::GetInfixVar()
{
	int count = 0;
	for (int i = 0; i < LenInf; i++)
	{
		if (isalpha(infix[i]))	count++;
	}
	return count;
}