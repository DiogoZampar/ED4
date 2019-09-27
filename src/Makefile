
siguel: main.o lista.o formas.o hidrantes.o quadras.o semaforos.o torres.o predios.o muros.o segmentos.o geometria.o heapsort.o arqGEO.o arqQRY.o
	gcc main.o lista.o formas.o hidrantes.o quadras.o semaforos.o torres.o predios.o muros.o segmentos.o geometria.o heapsort.o arqGEO.o arqQRY.o -o siguel -lm

main.o: main.c geometria.h
	gcc -c main.c -o main.o -fstack-protector-all -std=c99 

lista.o: lista.c lista.h
	gcc -c lista.c -o lista.o -fstack-protector-all -std=c99

formas.o: formas.c formas.h geometria.h
	gcc -c formas.c -o formas.o -fstack-protector-all -std=c99

hidrantes.o: hidrantes.c hidrantes.h
	gcc -c hidrantes.c -o hidrantes.o -fstack-protector-all -std=c99

quadras.o: quadras.c quadras.h geometria.h
	gcc -c quadras.c -o quadras.o -fstack-protector-all -std=c99

semaforos.o: semaforos.c semaforos.h
	gcc -c semaforos.c -o semaforos.o -fstack-protector-all -std=c99

torres.o: torres.c torres.h
	gcc -c torres.c -o torres.o -fstack-protector-all -std=c99
	
predios.o: predios.c predios.h
	gcc -c predios.c -o predios.o -fstack-protector-all -std=c99
	
muros.o: muros.c muros.h
	gcc -c muros.c -o muros.o -fstack-protector-all -std=c99
	
segmentos.o: segmentos.c segmentos.h
	gcc -c segmentos.c -o segmentos.o -fstack-protector-all -std=c99

geometria.o: geometria.c geometria.h
	gcc -c geometria.c -o geometria.o -fstack-protector-all -std=c99

heapsort.o: heapsort.c heapsort.h
	gcc -c heapsort.c -o heapsort.o -fstack-protector-all -std=c99

arqGEO.o: arqGEO.c arqGEO.h
	gcc -c arqGEO.c -o arqGEO.o -fstack-protector-all -std=c99

arqQRY.o: arqQRY.c arqQRY.h
	gcc -c arqQRY.c -o arqQRY.o -fstack-protector-all -std=c99

clean:
	rm *.o siguel
