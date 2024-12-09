# Bigerrno

42 School project with [@Lucie-Kin](https://github.com/Lucie-Kin) and [@LycorisDev](https://github.com/LycorisDev) based on Bash 3.  
It is customary to name one's shell, and we chose bigerrno. It is a pun mixing the French word *bigorneau*, which is a seashell, and the idea of a big mistake with "big" and "errno", aka "error number".  

---

## List of extra features

**Environment**
- variable lists: environment, hidden environment and local vars
- environment: set a few vital variables when the environment is empty on shell startup
- expand `$$` (PID), `$0` (argv[0]) and environment variables in shell and also in heredoc if not delimiter
- expand tilde `~`, `~+` and `~-`
- increment SHLVL when opening a shell (yes we have the list of shells), and decrement within a command (e.g. `env | grep SHLVL`)

**Builtins**
- echo = on top of `-n`, `-e` and no option
- cd = on top of a relative or absolute path, `-` and no option 
- export = also append option `a += b`
- handle Schrödinger paths: `mkdir dir1 && cd dir1 && mkdir dir2 && cd dir2 && rm -rf ../../dir1`

**History**
- add heredoc to history

**Parsing**
- backslash to concatenate two lines in shell and heredocs
- backslash to escape characters
- interpret special characters in `$'string'` and "echo -e", including Unicode sequences (e.g.: 🐚 $'\U1F41A')
- multi-line input (see it by copy-pasting several lines at once)
- prompt for more input in case of unclosed quote

**Wildcard**
- expand asterisk wildcards with any path given, not just the current directory (still no subdirectory)

**Aesthetic**
- prompt: identical to bash `user@host:path$ ` even with an empty environment
- colors: Ubuntu GNOME themed text and background
- window title: 🐚 set to the prompt 🐚
- opening a shell: reset the background color and window title
- lulu = change of terminal background and prompt colors
- matrix = green random letters with black background raining down the screen
- disco = annoying endless call of lulu in an epileptic non-friendly fashion
