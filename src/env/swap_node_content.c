#include "bigerrno.h"

void	swap_node_content(t_env *s1, t_env *s2)
{
	int		tmp_bool;
	char	*tmp_key;
	char	*tmp_value;

	tmp_bool = s1->withvalue;
	s1->withvalue = s2->withvalue;
	s2->withvalue = tmp_bool;
	tmp_key = s1->key;
	s1->key = s2->key;
	s2->key = tmp_key;
	tmp_value = s1->value;
	s1->value = s2->value;
	s2->value = tmp_value;
	return ;
}
