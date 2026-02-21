# Task Management System (C)

A menu-driven Task Management System implemented in C.  
The program loads tasks from `tasks.txt`, stores unperformed tasks in a **linked list**, allows performing tasks and undoing the last performed task using a **stack**, and generates a summary report in `Report.txt`.

## What I implemented (main.c)

### Data Structures
- **Linked List**: to store **Unperformed Tasks**
- **Stack**: to store **Performed Tasks** (LIFO) and support **Undo**
- **Linked List**: to store **Undone Tasks** (tasks restored back after undo)

### Main Features (Menu Options)
1. **Load Tasks File**: reads tasks from `tasks.txt` and inserts them into the tasks list.
2. **Add a New Task**: adds a task (checks that the ID is not duplicated).
3. **Delete a Task**: deletes a task by Task ID.
4. **Search for a Task**:
   - search by **ID**
   - search by **Name**
5. **View Unperformed Tasks**: prints all tasks currently in the linked list.
6. **Perform a Task**:
   - finds the task by ID
   - pushes it into the performed stack
   - deletes it from the unperformed list
7. **Undo Last Performed Task**:
   - pops the last performed task from the stack
   - adds it back to the unperformed list
   - stores it also in the undone list
8. **View Performed Tasks**:
   - prints tasks in the performed stack (without losing them)
   - uses a copy stack to restore the original stack content
9. **Generate Summary Report** (`Report.txt`):
   - Unperformed tasks
   - Performed tasks
   - Undone tasks
10. Exit

## Input File Format (tasks.txt)
Each line must follow this format:

`ID#TaskName#TaskDate#Duration`

Example:
10#meeting#22/3/2025#1.5
11#attend lecture#25/3/2025#3

## Output File
- `Report.txt` is generated using option **9** in the menu.

## How to Compile & Run
Compile:
```bash
gcc main.c -o taskmanager
./taskmanager
