CC = gcc
CFLAGS = -Wall -Wextra

	
stringtest: string_exercise_tests.c string_exercise.c
	$(CC) $(CFLAGS) -o stringtest string_exercise_tests.c string_exercise.c
	
run: stringtest
	./stringtest 
clean:
	rm -f stringtest
