# Grade Manager CLI

This C program manages student grade records from a structured text file. It allows reading, validating, modifying, and saving grade data through a command-line interface.

---

## 📄 File Format

Each line in the input file should follow this format:

<studentId>:<assignmentName>:<grade>

- `studentId`: A 10-digit number (e.g., `1234567890`)
- `assignmentName`: A string up to 20 characters
- `grade`: A number between 0 and 100

### Example:

1234567890:HW1:95
0987654321:Project1:88

---

## 🧰 Compilation

Compile the program using `gcc`:

gcc main.c function.c -o grades

> Note: `function.c` should contain the implementations for functions declared in `function.h`.

---

## 🚀 Running the Program

./grades data.txt

- `data.txt` is the input file with existing grade entries.
- After launching, the program will accept commands via standard input (`stdin`).

---

## 💬 Supported Commands

### 📃 `print`

Prints all grade entries.

print

---

### ➕ `add`

Adds a new grade entry.

add 1234567890:HW2:90

---

### ❌ `remove`

Removes a grade entry based on student ID and assignment name.

remove 1234567890:HW2

---

### 📊 `stats`

Shows statistics (e.g., average, min, max) for an assignment.

stats HW1
