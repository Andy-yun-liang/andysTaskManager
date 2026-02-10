# andysTaskManager

A lightweight command-line task manager built in C++.

## Installation

### 1. Install g++

**Windows**
```powershell
winget install -e --id GNU.GCC
```
**Ubuntu/Debian**
```bash
sudo apt install g++
```
**macOS**

g++ comes pre-installed, no action needed.

### 2. Clone & Build
```bash
git clone https://github.com/andy-yun-liang/andysTaskManager.git
cd andysTaskManager
g++ main.cpp task.cpp -o andysTaskManager
sudo cp andysTaskManager /usr/local/bin/andysTaskManager
```


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
