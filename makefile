Socket_server : main_server.o engine_server.o
	@gcc -o Socket_server main_server.o engine_server.o

main_server.o : main_server.c
	@gcc -c main_server.c

engine_server.o : engine_server.c header.h
	@gcc -c engine_server.c


Socket_client : main_client.o engine_client.o
	@gcc -o Socket_client main_client.o engine_client.o

main_client.o : main_client.c
	@gcc -c main_client.c

engine_client.o : engine_client.c header.h
	@gcc -c engine_client.c

clean :
	rm *.o
	rm Socket_server
	rm Socket_client
	rm test	
