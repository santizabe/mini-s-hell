# Minishell 🐚

A minimalist UNIX shell inspired by bash, developed as part of [42 School](https://www.42.fr/) curriculum. Implements core shell functionalities including command execution, pipes, redirections, and environment variables.

![Demo GIF]()

---

## 📋 Table of Contents
1. [🧠 Features](#-features)
2. [⚙️ Compilation](#️-compilation)
3. [🚀 Usage](#-usage)
4. [🔧 Built-ins](#-built-ins)
5. [🌍 Environment Variables](#-environment-variables)
6. [📜 Examples](#-examples)
8. [👥 Authors](#-authors)

---

## 🧠 Features
| Feature            | Status | Notes |
|--------------------|--------|-------|
| External commands (e.g., `/bin/ls`) | ✅ | Full PATH resolution |
| **Pipes** (`\|`) | ✅ | Supports multiple pipes (`cmd1 \| cmd2 \| cmd3`)|
| **Redirections** (`>`, `>>`, `<`, `<<`) | ✅ | Includes heredoc (`<<`) |
| **Environment variables** (`$HOME`) | ✅ | Expansion and inheritance |
| **Signals** (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`) | ✅ | Graceful process interruption |
| **Built-ins** (`cd`, `export`, etc.) | ✅ | See [built-ins](#-built-ins) |
| **Command history** (with ↑/↓ arrows) | ✅ | Persists across sessions |

---

## ⚙️ Compilation

### Requirements
- Linux or mac
- GCC (GNU Compiler Collection)
- GNU Make
- `readline` library (for command history)

### 🐧 Linux (Debian/Ubuntu)

```bash
sudo apt-get install gcc make libreadline-dev  # If readline is not installed
git clone https://github.com/your-username/minishell.git
cd minishell
make
./minishell
```

### 🍎 macOS

```bash
brew install readline  # If not installed
git clone https://github.com/your-username/minishell.git
cd minishell
make
./minishell
```

> ⚠️ **Note:** If `readline` is missing, compilation will fail.

## 🚀 Usage
```bash
$ ./minishell  
minishell> ls -la | grep "README"  # Pipes work  
minishell> echo "Hello $USER"      # Env var expansion  
minishell> cat < input.txt > output.txt  # Redirections  
minishell> exit  # Quit shell  
```

## 🔧 Built-ins
| Command                  | Description                     |
|--------------------------|---------------------------------|
| `cd [dir]`, `cd`, `cd -` | Change directory                |
| `export VAY=value`       | Set environment variable        |
| `unset VAR`              | Remove environment variable     |
| `echo [args]`            | Print text (suport `-n` flag)   |
| `pwd`                    | Print working directory         |
| `env`                    | List environment variables      |
| `exit [status]`          | Quit shell (optional exit code) |


## 🌍 Environment Variables
- Inherits parent shell env (`PATH`, `HOME`, `USER`, etc.).
- Supports expansions (`echo $HOME` → `/home/user`).

## 📜 Examples

### 1. Pipes & Redirecitons

```bash
minishell> cat file.txt | sort | uniq > sorted.txt
```

### 2. Heredoc (Here Document)

```bash
minishell> cat << EOF  
> Hello, Minishell!  
> EOF  
```

## 👥 Authors

| [<img src="https://avatars.githubusercontent.com/u/60015042?v=4" width=115><br><sub>Santiago Zapata Bedoya</sub>](https://github.com/santizabe) |  [<img src="https://avatars.githubusercontent.com/u/147926495?s=400&u=c32592a471205ad1232e7f95aa0a8d687bb47b37&v=4" width=115><br><sub>Fernando Osuna Granados</sub>](https://github.com/fog-3) |
| :---: | :---: |
