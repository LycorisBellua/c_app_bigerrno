# Bigerrno

It started as a school project with [@Lucie-Kin](https://github.com/Lucie-Kin) 
and [@LycorisBellua](https://github.com/LycorisBellua) based on Bash 3. Then, 
I've decided to continue to work on it.  

In our school, it is customary to name one's shell, and we chose "bigerrno". 
It's a pun mixing the French word *bigorneau*, which is a seashell, and the 
idea of a big mistake with "big" and "errno", aka "error number".  

---

## List of extra features

**Environment**
- Variable lists: environment, hidden environment and local vars.
- Environment: set a few vital variables when the environment is empty on shell 
startup.
- Expand `$$` (PID), `$0` (argv[0]) and environment variables in shell and also 
in heredoc if not delimiter.
- Expand tilde `~`, `~+` and `~-`.
- Increment SHLVL when opening a shell (yes we have the list of shells), and 
decrement within a command (e.g. `env | grep SHLVL`).

**Builtins**
- `echo`: on top of `-n`, `-e` and no option.
- `cd`: on top of a relative or absolute path, `-` and no option.
- `export`: also append option `a += b`.
- Handle Schrödinger paths: `mkdir dir1 && cd dir1 && mkdir dir2 && cd dir2 && 
rm -rf ../../dir1`.

**Original Builtins (Lucie)**
- `disco`: annoying endless call of `lulu` in an epileptic non-friendly fashion.
- `lulu`: change of terminal background and prompt colors.
- `matrix`: green random letters with black background raining down the screen.
- `shoot`: shoot a bullet before displaying the prompt.

**History**
- Add heredoc to history.

**Parsing**
- Backslash to concatenate two lines in shell and heredocs.
- Backslash to escape characters.
- Interpret special characters in `$'string'` and `echo -e`, including Unicode 
sequences (e.g.: 🐚 $'\U1F41A').
- Multi-line input (see it by copy-pasting several lines at once).
- Prompt for more input in case of unclosed quote.

**Wildcard**
- Expand asterisk wildcards with any path given, not just the current directory 
(still no subdirectory).

**Signals**
- Output the correct flavor text when an external command terminates from a 
signal.

**Aesthetic**
- Prompt: identical to bash `user@host:path$ ` even with an empty environment.
- colors: Ubuntu GNOME themed text and background.
- Window title: 🐚 set to the prompt 🐚.
- Opening a shell: reset the background color and window title.
