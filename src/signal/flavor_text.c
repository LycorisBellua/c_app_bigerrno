#include "bigerrno.h"

/*
	- `bash` + `kill -l` to list the signals.
	- Call function `strsignal(signum)` in C to see the default flavor text.
	- Run Bash and then a test program which sends a signal to itself. You'll 
	see which flavor text Bash decides to output, as it can be different from
	default.

	```
	#include <errno.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <signal.h>

	int	main(int argc, char **argv)
	{
		int	signum;

		signum = 0;
		if (argc > 1)
			signum = atoi(argv[1]);
		kill(getpid(), signum);
		return (errno);
	}
	```
*/

/*
	TODO
	- From signum 19 to 22, it's a background job:
		Signal 19: `[1]+  Stopped                 ./test 19`
		Signal 20: `[1]+  Stopped                 ./test 20`
		Signal 21: `[1]+  Stopped                 ./test 21`
		Signal 22: `[1]+  Stopped                 ./test 22`
*/

static void	populate_sig_flavor_text_0(char *sig_flavor_text[65]);
static void	populate_sig_flavor_text_1(char *sig_flavor_text[65]);
static void	populate_sig_flavor_text_2(char *sig_flavor_text[65]);

char	*get_sig_flavor_text(int signum)
{
	static char	*sig_flavor_text[65];

	if (!sig_flavor_text[0])
		populate_sig_flavor_text_0(sig_flavor_text);
	if (signum < 0 || signum > 64)
		return (sig_flavor_text[0]);
	return (sig_flavor_text[signum]);
}

static void	populate_sig_flavor_text_0(char *sig_flavor_text[65])
{
	sig_flavor_text[0] = "Unknown signal\n";
	sig_flavor_text[1] = "Hangup\n";
	sig_flavor_text[2] = "\n";
	sig_flavor_text[3] = "Quit (core dumped)\n";
	sig_flavor_text[4] = "Illegal instruction (core dumped)\n";
	sig_flavor_text[5] = "Trace/breakpoint trap (core dumped)\n";
	sig_flavor_text[6] = "Aborted (core dumped)\n";
	sig_flavor_text[7] = "Bus error (core dumped)\n";
	sig_flavor_text[8] = "Floating point exception (core dumped)\n";
	sig_flavor_text[9] = "Killed\n";
	sig_flavor_text[10] = "User defined signal 1\n";
	sig_flavor_text[11] = "Segmentation fault (core dumped)\n";
	sig_flavor_text[12] = "User defined signal 2\n";
	sig_flavor_text[13] = "";
	sig_flavor_text[14] = "Alarm clock\n";
	sig_flavor_text[15] = "Terminated\n";
	sig_flavor_text[16] = "Stack fault\n";
	sig_flavor_text[17] = "\n";
	sig_flavor_text[18] = "\n";
	sig_flavor_text[19] = "Stopped\n";
	sig_flavor_text[20] = "Stopped\n";
	sig_flavor_text[21] = "Stopped\n";
	sig_flavor_text[22] = "Stopped\n";
	populate_sig_flavor_text_1(sig_flavor_text);
	return ;
}

static void	populate_sig_flavor_text_1(char *sig_flavor_text[65])
{
	sig_flavor_text[23] = "\n";
	sig_flavor_text[24] = "CPU time limit exceeded (core dumped)\n";
	sig_flavor_text[25] = "File size limit exceeded (core dumped)\n";
	sig_flavor_text[26] = "Virtual timer expired\n";
	sig_flavor_text[27] = "Profiling timer expired\n";
	sig_flavor_text[28] = "\n";
	sig_flavor_text[29] = "I/O possible\n";
	sig_flavor_text[30] = "Power failure\n";
	sig_flavor_text[31] = "Bad system call (core dumped)\n";
	sig_flavor_text[32] = "Unknown signal 32\n";
	sig_flavor_text[33] = "Unknown signal 33\n";
	sig_flavor_text[34] = "Real-time signal 0\n";
	sig_flavor_text[35] = "Real-time signal 1\n";
	sig_flavor_text[36] = "Real-time signal 2\n";
	sig_flavor_text[37] = "Real-time signal 3\n";
	sig_flavor_text[38] = "Real-time signal 4\n";
	sig_flavor_text[39] = "Real-time signal 5\n";
	sig_flavor_text[40] = "Real-time signal 6\n";
	sig_flavor_text[41] = "Real-time signal 7\n";
	sig_flavor_text[42] = "Real-time signal 8\n";
	sig_flavor_text[43] = "Real-time signal 9\n";
	sig_flavor_text[44] = "Real-time signal 10\n";
	sig_flavor_text[45] = "Real-time signal 11\n";
	populate_sig_flavor_text_2(sig_flavor_text);
	return ;
}

static void	populate_sig_flavor_text_2(char *sig_flavor_text[65])
{
	sig_flavor_text[46] = "Real-time signal 12\n";
	sig_flavor_text[47] = "Real-time signal 13\n";
	sig_flavor_text[48] = "Real-time signal 14\n";
	sig_flavor_text[49] = "Real-time signal 15\n";
	sig_flavor_text[50] = "Real-time signal 16\n";
	sig_flavor_text[51] = "Real-time signal 17\n";
	sig_flavor_text[52] = "Real-time signal 18\n";
	sig_flavor_text[53] = "Real-time signal 19\n";
	sig_flavor_text[54] = "Real-time signal 20\n";
	sig_flavor_text[55] = "Real-time signal 21\n";
	sig_flavor_text[56] = "Real-time signal 22\n";
	sig_flavor_text[57] = "Real-time signal 23\n";
	sig_flavor_text[58] = "Real-time signal 24\n";
	sig_flavor_text[59] = "Real-time signal 25\n";
	sig_flavor_text[60] = "Real-time signal 26\n";
	sig_flavor_text[61] = "Real-time signal 27\n";
	sig_flavor_text[62] = "Real-time signal 28\n";
	sig_flavor_text[63] = "Real-time signal 29\n";
	sig_flavor_text[64] = "Real-time signal 30\n";
	return ;
}
