*This project has been created as part of the 42 curriculum by Shoaib Al-kawaldeh [sal-kawa] | Ismail khalil [ikhalil].*

# Bahgat Shell ☠️

A minimal Unix shell implementation written in C, built from scratch as part of the **42 School** `minishell` project.

---

## Description

**Bahgat Shell** is a simplified recreation of **bash**, the Bourne-Again Shell. The goal of this project is to deepen understanding of how a Unix shell works under the hood — including process creation, file descriptor management, signal handling, and command parsing.

The shell reads user input, tokenizes and parses it, expands environment variables, and executes commands by forking child processes. It supports pipes, redirections, here-documents, and a set of built-in commands, closely mimicking the behavior of bash.

### Key Features

- **Interactive prompt** with command-line editing via the `readline` library.
- **Pipes** (`|`) — chain multiple commands together.
- **Redirections** — input (`<`), output (`>`), append (`>>`), and here-doc (`<<`).
- **Environment variable expansion** — `$VAR` and `$?` (last exit status).
- **Quote handling** — single quotes (`'`) preserve literal values; double quotes (`"`) allow variable expansion.
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` behave like in bash.
- **Built-in commands:**
  - `echo` (with `-n` option)
  - `cd` (relative and absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## Instructions

### Prerequisites

- A Unix-like operating system (Linux / macOS)
- `cc` (C compiler with C99 support)
- `make`
- `readline` library installed

On Debian/Ubuntu, install readline with:
```bash
sudo apt-get install libreadline-dev
```

On macOS (with Homebrew):
```bash
brew install readline
```

### Compilation

Clone the repository and build:
```bash
git clone https://github.com/yourusername/Bahgat_Shell.git
cd Bahgat_Shell
make
```

The `Makefile` supports the following rules:

| Rule       | Description                              |
|------------|------------------------------------------|
| `make`     | Compile the project (with libft)         |
| `make clean` | Remove object files                   |
| `make fclean` | Remove object files and the binary   |
| `make re`  | Full recompile                           |

### Execution

```bash
./Bahgat_Shell
```

You will be greeted with an interactive prompt. Type any command just like you would in bash:

```
Bahgat_Shell$ echo "Hello, World!"
Hello, World!
Bahgat_Shell$ ls -la | grep src
Bahgat_Shell$ cat < input.txt > output.txt
Bahgat_Shell$ export MY_VAR=42
Bahgat_Shell$ echo $MY_VAR
42
Bahgat_Shell$ exit
```

---

## Project Structure

```
Bahgat_Shell/
├── Makefile
├── README.md
├── ascii_image.txt
├── readline_curses.supp
├── inc/
│   └── minishell.h
├── libft/
│   ├── Makefile
│   ├── inc/
│   │   ├── ft_printf.h
│   │   ├── get_next_line.h
│   │   └── libft.h
│   └── src/
│       ├── ft_is/
│       │   ├── ft_isalnum.c
│       │   ├── ft_isalpha.c
│       │   ├── ft_isascii.c
│       │   ├── ft_isdigit.c
│       │   ├── ft_isprint.c
│       │   └── ft_isspace.c
│       ├── ft_lst/
│       │   ├── ft_lstadd_back_bonus.c
│       │   ├── ft_lstadd_front_bonus.c
│       │   ├── ft_lstclear_bonus.c
│       │   ├── ft_lstdelone_bonus.c
│       │   ├── ft_lstiter_bonus.c
│       │   ├── ft_lstlast_bonus.c
│       │   ├── ft_lstmap_bonus.c
│       │   ├── ft_lstnew_bonus.c
│       │   └── ft_lstsize_bonus.c
│       ├── ft_mem/
│       │   ├── ft_bzero.c
│       │   ├── ft_calloc.c
│       │   ├── ft_memchr.c
│       │   ├── ft_memcmp.c
│       │   ├── ft_memcpy.c
│       │   ├── ft_memmove.c
│       │   └── ft_memset.c
│       ├── ft_printf/
│       │   ├── ft_count.c
│       │   ├── ft_hexa.c
│       │   ├── ft_hexatwo.c
│       │   ├── ft_pointer.c
│       │   ├── ft_printf.c
│       │   ├── ft_putchar.c
│       │   ├── ft_putnbr.c
│       │   ├── ft_putstr.c
│       │   └── ft_unsigned.c
│       ├── ft_put/
│       │   ├── ft_putchar_fd.c
│       │   ├── ft_putendl_fd.c
│       │   ├── ft_putnbr_fd.c
│       │   └── ft_putstr_fd.c
│       ├── ft_str/
│       │   ├── ft_split.c
│       │   ├── ft_strcat.c
│       │   ├── ft_strchr.c
│       │   ├── ft_strcmp.c
│       │   ├── ft_strcpy.c
│       │   ├── ft_strdup.c
│       │   ├── ft_striteri.c
│       │   ├── ft_strjoin.c
│       │   ├── ft_strlcat.c
│       │   ├── ft_strlcpy.c
│       │   ├── ft_strlen.c
│       │   ├── ft_strmapi.c
│       │   ├── ft_strncmp.c
│       │   ├── ft_strncpy.c
│       │   ├── ft_strndup.c
│       │   ├── ft_strnstr.c
│       │   ├── ft_strrchr.c
│       │   ├── ft_strtrim.c
│       │   └── ft_substr.c
│       ├── ft_to/
│       │   ├── ft_atoi.c
│       │   ├── ft_itoa.c
│       │   ├── ft_tolower.c
│       │   └── ft_toupper.c
│       └── get_next_line/
│           ├── get_next_line.c
│           └── get_next_line_utils.c
└── src/
    ├── main.c
    ├── allocate/
    │   ├── command.c
    │   ├── command_two.c
    │   ├── command_three.c
    │   ├── dir.c
    │   └── operator.c
    ├── builtin/
    │   ├── ft_cd.c
    │   ├── ft_echo.c
    │   ├── ft_exit.c
    │   ├── ft_pwd.c
    │   ├── ft_unset.c
    │   ├── is_builtin_function.c
    │   ├── env/
    │   │   ├── ft_env.c
    │   │   └── pwd_and_shlvl.c
    │   └── ft_export/
    │       ├── ft_export.c
    │       ├── ft_export_utils_one.c
    │       ├── ft_export_utils_two.c
    │       ├── ft_export_utils_three.c
    │       └── ft_export_utils_four.c
    ├── execute/
    │   ├── check_dir.c
    │   ├── get_path.c
    │   ├── here_doc.c
    │   ├── here_doc_two.c
    │   ├── pipe_one.c
    │   ├── pipe_two.c
    │   ├── pipe_three.c
    │   ├── pipe_four.c
    │   ├── pipe_five.c
    │   └── redirection.c
    ├── expander/
    │   ├── expand_tokens.c
    │   ├── expand_tokens_two.c
    │   ├── expand_tokens_three.c
    │   └── process_dollar_sign.c
    ├── free/
    │   ├── error_exit.c
    │   └── ft_free.c
    ├── main_utils/
    │   ├── utils_one.c
    │   ├── utils_two.c
    │   ├── utils_three.c
    │   ├── utils_four.c
    │   ├── utils_five.c
    │   ├── utils_six.c
    │   └── utils_seven.c
    ├── signals/
    │   └── handle_signals.c
    └── split/
        ├── check_operator.c
        ├── split_ft_echo.c
        ├── split_ft_echo_utils1.c
        ├── split_ft_echo_utils2.c
        ├── split_ft_export.c
        ├── split_input.c
        ├── split_utils1.c
        ├── split_utils2.c
        ├── split_utils3.c
        └── tokenizer/
            ├── split_command_one.c
            ├── split_command_two.c
            ├── split_command_three.c
            └── split_command_four.c
```

---

## Technical Choices

- **Custom libft** — the project uses a custom C standard library (`libft`) built from previous 42 projects, including `ft_printf` and `get_next_line`.
- **Tokenizer-based parsing** — input is split into tokens, then categorized into commands, operators, and redirections for structured execution.
- **No AST** — the shell uses array-based data structures rather than an abstract syntax tree, keeping the architecture straightforward.
- **Valgrind suppression** — a `readline_curses.supp` file is provided to suppress known readline/curses memory leak false positives when testing with Valgrind.

---

## Resources

- [Bash Reference Manual (GNU)](https://www.gnu.org/software/bash/manual/bash.html) — the definitive reference for bash behavior.
- [The Open Group Base Specifications — Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — POSIX shell specification.
- [Writing Your Own Shell (Stephen Brennan)](https://brennan.io/2015/01/16/write-a-shell-in-c/) — a beginner-friendly tutorial on building a shell in C.
- [Minishell — 42 Docs](https://harm-smits.github.io/42docs/projects/minishell) — community documentation for the 42 minishell project.
- [Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for the GNU readline library.
- [Pipes, Forks, & Dups: Understanding Command Execution and I/O](https://www.rozmichelle.com/pipes-forks-dups/) — visual guide to Unix process and I/O concepts.
