#include "parser.h"

int	is_metacharacter(char c)
{
	return (c == '(' || c == ')' || c == '&' || c == '|' || c == '<'
		|| c == '>' || c == ';');
}
