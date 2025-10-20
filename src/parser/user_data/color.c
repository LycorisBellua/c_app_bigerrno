#include "bigerrno.h"

#define PROMPT_COLOR_GREEN  "\001\e[1;32m\002"
#define PROMPT_COLOR_PEACH  "\001\e[1;38;5;208m\002"
#define PROMPT_COLOR_POWDER "\001\e[1;34m\002"
#define PROMPT_COLOR_AZUR   "\001\e[1;38;5;18m\002"
#define PROMPT_COLOR_PURPLE "\001\e[1;38;5;183m\002"
#define PROMPT_COLOR_PINK   "\001\e[1;35m\002"

#define BACKGROUND_COLOR_GNOME  "\033]11;rgb:3030/0a0a/2424\007"
#define BACKGROUND_COLOR_PEACH  "\033]11;rgb:aaaa/5555/5050\007"
#define BACKGROUND_COLOR_POWDER "\033]11;rgb:afaf/d0d0/e1e1\007"
#define BACKGROUND_COLOR_AZUR   "\033]11;rgb:1010/5050/aaaa\007"
#define BACKGROUND_COLOR_PURPLE "\033]11;rgb:3030/0a0a/5050\007"
#define BACKGROUND_COLOR_PINK   "\033]11;rgb:aaaa/5555/9999\007"

void	handle_default_background_color(int set)
{
	static char		color[42];
	struct termios	oldt;
	struct termios	newt;
	size_t			i;

	if (!color[0])
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		ft_putstr_fd("\033]11;?\007", STDOUT_FILENO);
		i = 0;
		while (i < sizeof(color) - 1)
		{
			if (read(STDIN_FILENO, &color[i], 1) != 1 || color[i++] == '\007')
				break ;
		}
		color[i] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	if (color[0] && set)
		ft_putstr_fd(color, STDOUT_FILENO);
	return ;
}

void	set_prompt_color(t_sh *sh, t_color color)
{
	const char	*str_color;

	str_color = 0;
	if (color == E_COLOR_GNOME)
	{
		sh->prompt_color1 = PROMPT_COLOR_GREEN;
		sh->prompt_color2 = PROMPT_COLOR_POWDER;
		return ;
	}
	else if (color == E_COLOR_PEACH)
		str_color = PROMPT_COLOR_PEACH;
	else if (color == E_COLOR_POWDER)
		str_color = PROMPT_COLOR_POWDER;
	else if (color == E_COLOR_AZUR)
		str_color = PROMPT_COLOR_AZUR;
	else if (color == E_COLOR_PURPLE)
		str_color = PROMPT_COLOR_PURPLE;
	else if (color == E_COLOR_PINK)
		str_color = PROMPT_COLOR_PINK;
	sh->prompt_color1 = str_color;
	sh->prompt_color2 = str_color;
	return ;
}

void	set_background_color(t_color color)
{
	if (color == E_COLOR_GNOME)
		ft_putstr_fd(BACKGROUND_COLOR_GNOME, STDOUT_FILENO);
	else if (color == E_COLOR_PEACH)
		ft_putstr_fd(BACKGROUND_COLOR_PEACH, STDOUT_FILENO);
	else if (color == E_COLOR_POWDER)
		ft_putstr_fd(BACKGROUND_COLOR_POWDER, STDOUT_FILENO);
	else if (color == E_COLOR_AZUR)
		ft_putstr_fd(BACKGROUND_COLOR_AZUR, STDOUT_FILENO);
	else if (color == E_COLOR_PURPLE)
		ft_putstr_fd(BACKGROUND_COLOR_PURPLE, STDOUT_FILENO);
	else if (color == E_COLOR_PINK)
		ft_putstr_fd(BACKGROUND_COLOR_PINK, STDOUT_FILENO);
	return ;
}

void	reset_title_and_background_color(void)
{
	int	stdin_dup;

	if (isatty(STDIN_FILENO))
	{
		stdin_dup = dup(STDIN_FILENO);
		close(STDIN_FILENO);
		readline("\001\e]0;Terminal\a\002");
		dup2(stdin_dup, STDIN_FILENO);
		close(stdin_dup);
	}
	handle_default_background_color(1);
	return ;
}
