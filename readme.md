# void Shell

A simple command-line shell implemented in C inspired from  XV6 OS by MIT that supports various built-in commands, command history, and reminders. The shell is designed to be extensible and lightweight, making it suitable for educational purposes and basic shell operations.

## Features

- **Built-in Commands**: Supports various commands like `pwd`, `ls`, `cd`, `echo`, `cat`, `touch`, `psinfo`, and `remindme`.
- **Command History**: Navigate through previously entered commands using the up and down arrow keys.
- **Reminders**: Set reminders that notify you after a specified duration implemented using pthreads.
- **Dynamic Prompt**: Displays the current working directory in the prompt.

## Commands

| Command                         | Description                                                                 |
|---------------------------------|-----------------------------------------------------------------------------|
| `exit`,`.exit`,`quit`                          | Exit the shell.                                                            |
| `cd [dir]`                     | Change the current directory to `[dir]`.                                   |
| `pwd`                           | Print the current working directory.                                       |
| `ls [flags]`                   | List files in the current directory. Supports flags like `-l`, `-a`, `-h`. |
| `echo [msg]`                   | Print the message `[msg]` to the console, including text inside quotes.   |
| `cat [file]`                   | Display the contents of the specified `[file]`.                            |
| `touch [file]`                 | Create an empty file named `[file]`.                                       |
| `psinfo`                        | Display information about the current processes and their IDs.             |
| `remindme [time] [message]`    | Set a reminder to display `[message]` after `[time]` seconds.             |
| `overkill`                      | Kill all background processes associated with the shell.                   |

### Command Details

- **`exit`**: Terminates the shell session and exits the program.
- **`cd [dir]`**: Changes the shell's current working directory to the specified directory `[dir]`. If no directory is provided, it will navigate to the home directory.
- **`pwd`**: Outputs the path of the current working directory to the terminal.
- **`ls`**: Lists all files and directories in the current working directory. Supports flags (e.g., `-lah`).
- **`echo [msg]`**: Prints the specified message to the console. If the message is enclosed in double quotes, it prints the content inside the quotes.
- **`cat [file]`**: Reads and displays the contents of the specified file `[file]` on the terminal.
- **`touch [file]`**: Creates a new empty file named `[file]` or updates the timestamp of the file if it already exists.
- **`psinfo`**: Displays a list of currently running processes along with their Process IDs (PIDs).
- **`remindme [time] [message]`**: Sets a reminder that will display the specified `[message]` after waiting for `[time]` seconds.
- **`overkill`**: Terminates all background processes initiated by the shell.

## Usage

To run the shell manually, compile the C files and execute the resulting binary

or directly run the makefile 
```bash
  run: make
      ./void_shell
``````
