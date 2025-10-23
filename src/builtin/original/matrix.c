#include "bigerrno.h"

#define MATRIX "clear; while :; do echo \"$(tput lines) $(tput cols) \
$(( RANDOM % $(tput cols) )) $(( RANDOM % 73 ))\"; sleep 0.05; done | \
perl -e '$|=1; print \"\\033[?25l\"; \
$SIG{INT}=sub{print \"\\033[0m\\033[?25h\\n\"; exit 0;}; \
my $letters=\"abcdefghijklmnopqrstuvwxyz\
ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789@#$%^&*() \"; \
my %a; my %len; my %shrinking; my %speed; my %counter; my $prev_cols=0; \
my @trail=(\"\\033[38;5;22m\",\"\\033[38;5;28m\",\"\\033[38;5;34m\",\
\"\\033[38;5;40m\",\"\\033[38;5;46m\"); while(<>) { chomp; \
my ($rows,$cols,$x)=split; next unless defined $rows && defined $cols \
&& defined $x; if($cols!=$prev_cols){for my $col(keys %a){delete $a{$col} \
if $col>=$cols;} $prev_cols=$cols;} if(!exists $a{$x}){ $a{$x}=0; \
$len{$x}=3+int(rand(18)); $speed{$x}=0+int(rand(5)); $counter{$x}=0; } \
for my $col(keys %a){ $counter{$col}++; next if $counter{$col} < $speed{$col}; \
$counter{$col}=0; my $head=$a{$col}++; if($shrinking{$col}){ if($len{$col}>0){ \
my $start_row=$rows-$len{$col}+1; $start_row=1 if $start_row<1; for my \
$i(0..$len{$col}-1){my $row=$start_row+$i; last if $row>$rows; \
my $trail_letter=substr($letters,int(rand(length($letters))),1); \
my $color_index=int($i*@trail/$len{$col}); $color_index=@trail-1 if \
$color_index>@trail-1; printf \"%s\\033[%d;%dH%s\",$trail[$color_index],$row,\
$col+1,$trail_letter;} my $clear_row=$start_row-1; printf \"\\033[%d;%dH \",\
$clear_row,$col+1 if $clear_row>=1 && $clear_row<=$rows;} $len{$col}--; \
if($len{$col}<=0){printf \"\\033[%d;%dH \",$rows,$col+1; delete $a{$col}; \
delete $len{$col}; delete $shrinking{$col}; delete $speed{$col}; \
delete $counter{$col};} next;} if($head+1>=$rows){$shrinking{$col}=1; next;} \
for my $i(0..$len{$col}-1){my $row=$head-($len{$col}-1)+$i; next if $row<1 || \
$row>$rows; my $trail_letter=substr($letters,int(rand(length($letters))),1); \
my $color_index=int($i*@trail/$len{$col}); $color_index=@trail-1 if \
$color_index>@trail-1; printf \"%s\\033[%d;%dH%s\",$trail[$color_index],$row,\
$col+1,$trail_letter;} my $head_letter=substr($letters,\
int(rand(length($letters))),1); printf \"\\033[%d;%dH\\033[1;37m%s\\033[0;0H\",\
$head+1,$col+1,$head_letter; my $clear_row=$head-$len{$col}+1; \
printf \"\\033[%d;%dH \",$clear_row,$col+1 if $clear_row>=1 && \
$clear_row<=$rows; }}'"

static void	run_script(t_sh *sh);

int	builtin_matrix(t_sh *sh, char **arg)
{
	pid_t	pid;
	int		status;

	if (get_array_length((void **)arg) > 1)
	{
		ft_putstr_fd("You can only choose one!\n", STDERR_FILENO);
		return (42);
	}
	ft_putstr_fd("\x0c", STDOUT_FILENO);
	ft_putstr_fd("\033[H\033[J", STDOUT_FILENO);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (!pid)
		run_script(sh);
	status = 0;
	waitpid(pid, &status, 0);
	ft_putstr_fd("\x0c", STDOUT_FILENO);
	return (WIFEXITED(status) || 1);
}

static void	run_script(t_sh *sh)
{
	char	*args[4];

	args[0] = "/bin/bash";
	args[1] = "-c";
	args[2] = MATRIX;
	args[3] = 0;
	execve(args[0], args, convert_to_arr(sh->env));
	ft_putstr_fd(SHELL": execve matrix: fail", STDERR_FILENO);
	exit(1);
	return ;
}
