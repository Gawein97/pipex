# pipex
Simple Unix pipe simulation for shell

School 21 (Ecole 42) project. Provide a starting knowledge about unix processes and systems calls such as pipe and fork.
Bonus part - multiple pipe handling.

**this version is bound to ENV PATH. Which is not perfect realization for my opinion**

----
## how to use
1. Build project with bash$>make
2. run "**bash$>./pipex file1 cmd1 cmd2 file2**" wich is equivalent for "**bash$> < file cmd1 | cmd2 > file2**"
