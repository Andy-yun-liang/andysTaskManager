# andysTaskManager

A lightweight command-line task manager built in C++.

## Commands

| Command | Description |
|---------|-------------|
| `andysTaskManager add "description"` | Add a new task |
| `andysTaskManager ls` | List pending tasks |
| `andysTaskManager ls -a` | List all tasks including completed |
| `andysTaskManager done <id>` | Mark a task as complete |
| `andysTaskManager edit <id> "new text"` | Edit a task description |
| `andysTaskManager del <id>` | Delete a task |

## Data
Tasks are stored in `~/.andysTaskManager/notes.txt`.
