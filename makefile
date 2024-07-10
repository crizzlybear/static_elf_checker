program: checker.o CheckStackProtections.o CheckSyscalls.o GetFileType.o ReadFileToArray.o 
	gcc checker.o CheckStackProtections.o CheckSyscalls.o GetFileType.o ReadFileToArray.o -o checker
checker.o: checker.c commonHeaders.h modules.h 
	gcc -c checker.c
CheckStackProtections.o: CheckStackProtections.c commonHeaders.h modules.h
	gcc -c CheckStackProtections.c
CheckSyscalls.o: CheckSyscalls.c commonHeaders.h modules.h
	gcc -c CheckSyscalls.c
GetFileType.o: GetFileType.c commonHeaders.h modules.h
	gcc -c GetFileType.c
ReadFileToArray.o: ReadFileToArray.c commonHeaders.h modules.h
	gcc -c ReadFileToArray.c
clean: rm -f checker checker.o CheckStackProtections.o CheckSyscalls.o GetFileType.o ReadFileToArray.o