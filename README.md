> *This project has been created as part of the 42 curriculum by darismen*

# *minishell*

## Description

Minishell is a simplified Unix shell developed in C as part of the 42 curriculum. It recreates the essential behavior of a command-line interpreter, including command execution, pipes, redirections, environment-variable expansion, signal handling, and built-in commands.

The project supports:

- Interactive command execution
- Single and double quotes
- Pipes (`|`)
- Redirections (`<`, `>`, `>>`)
- Here-documents (`<<`)
- Environment-variable expansion
- Exit-status expansion (`$?`)
- Command history
- Signal handling
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## Instructions

Clone the repository and compile the project:

```bash
git clone <repository-url>
cd 03_minishell
make exe

## Resources

No AI was used in the elaboration of this project.

* https://harm-smits.github.io/42docs/projects/minishell
* https://medium.com/@august1.caes/minishell-a-comprehensive-guide-24cb30a342ec
* https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb
* https://github.com/gemartin99/Minishell