#A regra closest tem como dependência o arquivo objeto closest.o
#O comando cria um executável saida a partir do objeto closest.o
closest: closest.o
	gcc closest.o -o closest -lm

#A regra closest.o tem como dependência o arquivo fonte closest.c
#O arquivo objeto closest.o é criado a partir do arquivo fonte closest.c
closest.o: closest.c
	gcc -c closest.c

#A regra clean: apaga os arquivos .o ao digitarmos make clean no console
clean:
	rm -f *.o

#A regra execClean apaga o arquivo executável ao digitarmos make execClean no console
execClean:
	rm -f closest