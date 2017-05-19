
CC = /usr/bin/gcc
CFLAGS = -g -O0 -fopenmp
LD = /usr/bin/gcc
LDFLAGS = -g -fopenmp

PROGRAM1 = MatrixMultiplication
PROGRAM2 = MatrixMultiplication_Parallel

all:    ${PROGRAM1}.exe ${PROGRAM2}.exe

${PROGRAM1}.exe: ${PROGRAM1}.o cur_time.o
		${LD} ${PROGRAM1}.o cur_time.o -o ${PROGRAM1}.exe -lm

${PROGRAM1}.o: ${PROGRAM1}.c
		${CC} ${CFLAGS} -c $<

${PROGRAM2}.exe: ${PROGRAM2}.o cur_time.o
		${LD} ${LDFLAGS} ${PROGRAM2}.o cur_time.o -o ${PROGRAM2}.exe -lm

${PROGRAM2}.o: ${PROGRAM2}.c
		${CC} ${CFLAGS} -c $< -o ${PROGRAM2}.o

cur_time.o: cur_time.c
		${CC} ${CFLAGS} -c $<

clean:
		rm -f ${PROGRAM1}.o ${PROGRAM1}.exe ${PROGRAM2}.o ${PROGRAM2}.exe
