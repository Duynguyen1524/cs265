grades: function.c main.c
	 gcc -o grades main.c function.c

run: grades
	 ./grades
clean:
	 rm -f grades *.o