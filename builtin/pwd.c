#include "bigerrno.h"

static char	*get_cwd(t_sh *sh, const char *arg, int *code_err);
static void	update_oldpwd(t_sh *sh, t_env *pwd);

int	bigerrno_pwd(t_sh *sh)
{
	if (sh->pwd)
		printf("%s\n", sh->pwd);
	return (0);
}

int	update_pwd(t_sh *sh, const char *arg, int code_err)
{
	char	*cwd;
	t_env	*var;

	if (code_err)
		return (code_err);
	cwd = get_cwd(sh, arg, &code_err);
	if (!cwd)
		return (code_err);
	free(sh->pwd);
	sh->pwd = cwd;
	var = find_key(&sh->env, "PWD");
	if (var)
	{
		update_oldpwd(sh, var);
		free(var->value);
		var->value = ft_strdup(sh->pwd);
		var->withvalue = 1;
	}
	return (code_err);
}

static char	*get_cwd(t_sh *sh, const char *arg, int *code_err)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		tmp = ft_strjoin("getcwd: ", ERR_ACS_DIR);
		*code_err = output_error(EPERM, compose_err_msg("cd", ERR_CD, tmp,
					strerror(ENOENT)));
		free(tmp);
		tmp = ft_strjoin(sh->pwd, "/");
		cwd = ft_strjoin(tmp, arg);
		free(tmp);
	}
	return (cwd);
}

static void	update_oldpwd(t_sh *sh, t_env *pwd)
{
	t_env	*oldpwd;

	oldpwd = find_key(&sh->env, "OLDPWD");
	if (!oldpwd)
		oldpwd = find_key(&sh->hidden, "OLDPWD");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
		oldpwd->withvalue = 1;
	}
	else
	{
		oldpwd = lst_new("OLDPWD", pwd->value);
		if (oldpwd)
			lstadd_back(&sh->hidden, oldpwd);
	}
	return ;
}
