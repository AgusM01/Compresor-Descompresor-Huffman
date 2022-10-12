huffC: 
	gcc HuffmannCodificacion.c Arbol.c Elemento.c Codificacion.c io.c test.c
	valgrind -s ./a.out
huffD: 
	gcc HuffmannDecodificacion.c Arbol.c Elemento.c Decodificacion.c io.c test.c
	valgrind -s ./a.out
