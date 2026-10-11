# Minishell

> *As beautiful as a shell.*

A small Bash-like shell written in C, built as part of the **42 school** curriculum. Minishell reads commands, parses them, and executes them while handling pipes, redirections, environment variables, signals and a set of built-in commands, all from scratch (well, almost: we get to use `readline`).

```
➜  Minishell git:(main) ❯ echo "hello $USER" | tr a-z A-Z > greeting.txt
➜  Minishell git:(main) ❯ cat greeting.txt
HELLO THORGAL
```

---

## Features

**Prompt & input**
- Interactive prompt powered by GNU `readline`, with command history
- Prompt shows the current directory and, inside a Git repository, the current branch

**Parsing**
- Tokenizer with support for `'single quotes'` (no expansion) and `"double quotes"` (with `$` expansion)
- Environment variable expansion: `$VAR`, plus `$?` for the exit status of the last command
- Syntax checking for invalid pipes and redirections (e.g. `| ls`, `ls >`, `ls || wc`)

**Execution**
- Executes binaries found via `PATH`, or via relative / absolute paths
- Pipelines of any length: `cmd1 | cmd2 | cmd3 ...`
- Redirections:
  | Operator | Meaning |
  |----------|---------|
  | `<`  | Redirect input from a file |
  | `>`  | Redirect output to a file (truncate) |
  | `>>` | Redirect output to a file (append) |
  | `<<` | Here-document, read until the delimiter |

**Built-ins**
| Command | Notes |
|---------|-------|
| `echo`   | Supports `-n` (including `-nnn`) |
| `cd`     | Relative/absolute paths, `~`, `cd -`; updates `PWD` / `OLDPWD` |
| `pwd`    | No options |
| `export` | With no args, prints the sorted environment; validates identifiers |
| `unset`  | Removes variables from the environment |
| `env`    | No options or arguments |
| `exit`   | Optional numeric exit code |

**Signals**
- `Ctrl-C` shows a fresh prompt on a new line
- `Ctrl-D` exits the shell
- `Ctrl-\` does nothing at the prompt
- Child processes get default signal behaviour, and the exit status reflects it (`130`, `131`)

---

## Installation

### Requirements
- A Unix-like system (Linux or macOS)
- `cc` / `gcc` and `make`
- The GNU readline library

On Debian/Ubuntu:
```bash
sudo apt install build-essential libreadline-dev
```

On macOS (Homebrew):
```bash
brew install readline
```

### Build
```bash
git clone https://github.com/Thorga1/Minishell.git
cd Minishell
make
```

### Run
```bash
./minishell
```

### Make targets
| Target | Description |
|--------|-------------|
| `make` / `make all` | Builds `libft` and `minishell` |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Full rebuild |
| `make norminette` | Runs the 42 Norm checker on `src/` and `includes/` |

---

## Examples

```bash
# Pipes and redirections
ls -l | grep ".c" | wc -l > count.txt

# Append
echo "another line" >> log.txt

# Here-document
cat << EOF
Hello from a heredoc
EOF

# Quotes and expansion
export NAME=world
echo "hello $NAME"   # hello world
echo 'hello $NAME'   # hello $NAME

# Exit status
ls /nonexistent
echo $?              # 2 (or 1, depending on your ls)

# Navigation
cd ~/Documents
cd -
```

---

## Project structure

```
Minishell/
├── includes/
│   ├── minishell.h       # Structs, enums, prototypes
│   └── messages.h        # Colors, prompt formats, messages
├── libft/                # Our own C standard library
├── src/
│   ├── main/             # Entry point, REPL loop, prompt, signals
│   ├── tokens/           # Tokenizer, quote handling, expander, syntax checks
│   ├── exec/             # Command execution, pipes, redirections, heredocs
│   ├── builtins/         # echo, cd, pwd, export, unset, env, exit
│   └── utils/            # Env helpers, git helpers, memory cleanup
└── Makefile
```

### How a command flows through the shell

1. **Read**: `readline` grabs the line and adds it to history.
2. **Tokenize**: the input is split into tokens, respecting quotes.
3. **Expand**: `$VAR` and `$?` are replaced (except inside single quotes).
4. **Validate**: tokens are checked for syntax errors around pipes and redirections.
5. **Parse**: tokens are turned into a linked list of `t_cmd` nodes, each holding its arguments and a list of redirections.
6. **Execute**: a single built-in runs in the parent process; everything else is forked, wired up with pipes and redirections, and executed with `execve`.

---

## Limitations

As required by the subject, Minishell does **not** handle:
- `&&`, `||`, or wildcards `*` (bonus part)
- `;` and `\` (backslash escapes)
- Subshells `( )`, job control, or command substitution

---

## Authors

- **Thorgal Ordner** ([@Thorga1](https://github.com/Thorga1)), `tordner` @ 42
- **Leo Firmin**, `lfirmin` @ 42

---

<p align="center">Made with coffee and a lot of <code>valgrind</code> at 42.</p>