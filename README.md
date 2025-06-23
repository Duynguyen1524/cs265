# Grade Manager CLI

This is a C program for managing student grade records from a text file. It supports reading, validating, modifying, and saving structured grade data using command-line input.

## 📄 File Format

Each line in the input file should follow the format:


- `studentId`: A 10-digit number (e.g., `1234567890`)
- `assignmentName`: A string up to 20 characters
- `grade`: A number between 0 and 100

### Example:
1234567890:HW1:95
0987654321:Project1:88

## 🚀 How to Compile

Use `gcc` (e.g., via MSYS2 or Linux):

```bash
gcc main.c function.c -o grades
## How to run
./grades data.txt
