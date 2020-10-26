#ifdef __vita__
#include <psp2/sysmodule.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/display.h>
#include <psp2/ctrl.h>
#include <psp2/net/net.h>
#define printf psvDebugScreenPrintf
#else
#define NO_psvDebugScreenInit
#endif

#include <psp2/kernel/processmgr.h>
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>
//#include "debugScreen.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


#include "gfx.h"
#include "font.h"

//const char* font_path = "app0:/data/font.TTF";
char* serv = "192.168.43.88";
int port = 1234;

char *soko = "READ sokoban 1 10 25";
char *date = "READ date 1 1 25";

int main (__attribute__((unused)) int argc,  __attribute__((unused)) char *argv[]){
	//ajout perso
	char *msg = "NIQUE TOI";


	opendisplay(960,544);		//Setup everything for the display (640 400 Basic resolution)
	atexit(closedisplay);		//At exit use closedisplay
	initfont();

	solidrect(0,0,vxsize,vysize,0,0,0);
	copytoback(0);

	copyfromback(0);
	drawprintfxy(64,64,msg);
	copyup();


	delay(1000);

	copyfromback(0);
	drawprinttext(64,64,"HELLO WORLD\n LES GENS");
	copyup();


	delay(1000);
	// Request Part


	//char *url = NULL;// will point to wttr or rate

	//psvDebugScreenInit();
	//psvDebugScreenFont.size_w += 3;//narrow character printing
	//psvDebugScreenFont.size_h += 3;//narrow character printing
	//psvDebugScreenFont.size += 3;//narrow character printing

	//printf("Press [L]=%s%s [R]=%s%s\n", wttr[0], wttr[1], rate[0], rate[1]);

	static char net_mem[1*1024*1024];
	sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
	sceNetInit(&(SceNetInitParam){net_mem, sizeof(net_mem)});

	while (42)
	{
		char *url = NULL;
		char off = 'a';


		copyfromback(0);
		drawprinttext(64,64,"L sokoban\nR date");
		drawcharxy(128,128, off);
		copyup();

		for(SceCtrlData ctrl={}; !url; sceCtrlReadBufferPositive(0,&ctrl,1)){
			if(ctrl.buttons == SCE_CTRL_LTRIGGER)
			{
				msg = soko;
				url = serv;
			}
			if(ctrl.buttons == SCE_CTRL_RTRIGGER)
			{
				msg = date;
				url = serv;
			}

			if(ctrl.buttons == SCE_CTRL_DOWN)
			{
				off--;
			}
			if(ctrl.buttons == SCE_CTRL_UP)
			{
				off++;
			}

			copyfromback(0);
			drawprinttext(64,64,"L sokoban\nR date");
			drawcharxy(128,128, off);
			copyup();
		}

		//printf("fetching %s%s...\n", url[0], url[1]);
		int fd = socket(PF_INET, SOCK_STREAM, 0);
		connect(fd, (const struct sockaddr *)&((struct sockaddr_in){.sin_family = AF_INET, .sin_port = htons(port), .sin_addr.s_addr = *(long*)(gethostbyname(url)->h_addr)}), sizeof(struct sockaddr_in));

		//char*header[] = {"GET ",url[1]," HTTP/1.1\r\n", "User-Agent: curl/PSVita\r\n", "Host: ",url[0],"\r\n", "\r\n", 0};
		//for(int i = 0; header[i]; i++)//send all request header to the server
		//	write(fd, header[i], strlen(header[i]));
		write(fd, msg, strlen(msg));

		unsigned pos = 0;
		unsigned char c, line[4096];
		char *s = (char*)malloc(4000*sizeof(char));
		char *t = s;

		while(read(fd,&c,sizeof(c)) > 0 && pos < sizeof(line))
		{
			//if (c>>6==3) // if fetched char is a UTF8
				//c = readUTF(c,fd); // convert it back to ASCII
				if (c == '\n') { // end of line reached
					//psvDebugScreenPrintf("%.*s\n", pos, line); // printf the received line into the screen
					pos = 0; // reset the buffer pointer back to 0
				} else {
					line[pos] = c;
					pos++;
				}
				*t = c;
				t++;
		}
		close(fd);

		//sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
		//sceKernelDelayThread(~0);

		copyfromback(0);
		drawprinttext(64,64,s);
		copyup();

		delay(1000);
	}


	//delay(10000);
	sceNetTerm();
    sceKernelExitProcess(0);
	return 0;
}
