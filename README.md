Write a program called  myCopy that will require two inputs, an input file and an output file. This means that, from the command line, the user must enter the names of the input and output files as parameters to the program, as in:

myCopy /i=war.txt /o=peace.txt

where /i identifies the input file and /o identifies the output file. Notice that the order of parameters on the command line now becomes independent, as in 

myCopy /o=peace.txt /i=war.txt

is just as valid as the previous program invocation.

Once the program has  both the input and output files, the input file will then be copied to the output file. The program must warn the user if the output file already exists and and then terminate unless one of the following options are given as a parameter on the command line:

/e -> overwrite

/a -> append

This means that the input and output file names must be copied from argv to separate variables BEFORE you can determine if the file needs to opened for appending or not. If the /e  or /a option is not given, then the program should error out if the file already exists..
