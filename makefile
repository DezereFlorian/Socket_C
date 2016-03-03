Socket_server : main_server.o engine_server.o
	@gcc -o Socket_server main_server.o engine_server.o

main_engine.o : main_engine.c
	@gcc -c main_engine.c

engine_server.o : engine_server.c header.h
	@gcc -c engine_server.c


Socket_client : main_client.o header.h
	@gcc -o Socket_client main_client.o

main_client.o : main_client.c
	@gcc -c main_client.c

clean :
	rm *.o
	rm Socket_server
	rm Socket_client
