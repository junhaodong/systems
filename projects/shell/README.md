Shellfish
======
Junhao Dong  
Systems Programming, Period 8

Shell program  
Run with "make"  
Exit with "exit", "quit", or Ctrl-D at the start of a line


## Basic Features
- [x] Execute multiple commands per line, separated by `;`
  - [x] Trim excess white space
  - [x] Ignore consecutive semicolons rather than returning a syntax error
- [x] Basic file redirection: `<`, `>`, `>>`
- [x] Basic piping: `|`
- [x] Checked for memory leaks: Valgrind


## To Do
###Enhancements
------
- [x] Tilde expansion: `~` is interchangeable with user's $HOME directory
- [x] Color prompt:
  - [x] Username, hostname, current working directory
- [ ] Better redirection and piping:
  - [x] `cmd < in > out`
  - [x] `cmd > out1 flag1 flag2`
  - [x] `cmd1 | cmd2 | cmd3`
  - [x] `cmd1 | cmd2 > out1`
  - [ ] `<<`, `<<<`, redirection for `STDERR` and other file descriptors
- [x] Handle `EOF` (Ctrl-D)
- [x] Handle `SIGINT` (Ctrl-C)
- [ ] Command history & navigation
- [ ] Directory history & navigation (`cd -`)
- [ ] Wildcard `*`
- [ ] Tab completion: for files and commands
- [ ] Logic operators: `&&`, `||`, `!`
- [ ] Background processes: `&`


###Bugs to be fixed
------
- [ ] Allow redirect and pipe symbols to be adjacent to commands or flags (not separated by space)
- [ ] Allow tilde expansion to work in conjunction with redirection
- [ ] Have `SIGINT` re-print the prompt
- [ ] Fix: Exiting with EOF after using `~` expansion segfaults

## Function Headers
shell.h

- static void sigHandler(int signo)
  - Allows `SIGINT` to interrupt commands being executed by the shell rather than the shell itself by checking a global variable that stores the return value of fork()
- void printPrompt()
  - Prints the shell prompt with the current working directory, replacing $HOME with ~ when applicable
- char * trimSpace(char *str)
  - Returns a string without trailing and leading spaces and semicolons from a string
- void redirect()
  - Handles the redirection (calls to `dup2`) of file descriptors
- void safe_exec()
  - Executes the command in `argv` with `execvp` and safely frees all allocated memory before exitting if executing fails
- void executePipe(int pipeIndex)
  - Forks and separates `argv`, the global array of command arguments, on the pipeIndex into two arrays
  - The child executes the first command with `safe_exec`, writing into the pipe
  - The parent executes the rest of the command[s]  with `executeMisc` while reading out of the pipe
- void executeMisc()
  - Searches for any pipes `|` in global var `argv` and calls `executePipe` if it finds one. If not, it redirects if `parseInput` found a redirect symbol and finally calls `safe_exec`
- void execute()
  - Handles `exit` (or `quit`) and `cd` commands
  - Otherwise, forks and the child calls `executeMisc`
- char ** parseInput(char *input, char *delim)
  - Returns a dynamically allocated char **argv of input arguments separated by `delim`
  - The memory size of argv changes as more inputs are added by doubling the maximum memory size and reallocating when the current size approaches the maximum size
  - Arguments are trimmed of whitespace and semicolons with a call to `trimSpace`
  - Redirect symbols and the first argument afterwards are not added to argv. They set booleans `redir_out` and/or `redir_in` to true and the file is stored in a global variable. Error checking for faulty files is implemented
- void shell()
  - Continuously loops through the shell procedures: reading and parsing user input and then executing the commands
  - If the return value of `fgets` is null, the user has sent an EOF at the start of a line and the shell exits normally
