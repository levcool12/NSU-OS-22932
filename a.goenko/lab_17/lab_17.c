#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

int main() {
	char buf;
	struct termios old;
	int f = tcgetattr(0, &old);
	int c = 0;
	int s = 0;
	int fl = 0;
	int** str;
	str = (int**)malloc(sizeof(int*));
	str[0] = (int*)malloc(sizeof(int)*40);
	char* last;
	int il = 0;
	last = (char*)malloc(sizeof(char)*40);
	int count_w = 0;
	int* size_w;
	size_w = (int*)malloc(sizeof(int));
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
	f = tcsetattr(0, TCSANOW, &old);
	while(1){
		buf = getchar();
		if (buf == old.c_cc[VERASE]){
			printf("\b \b");
			str[s][c] = 0;
			size_w[count_w]--;
			il--;
			if (size_w[count_w] == 0){
				count_w--;
				il = size_w[count_w];
			}
			c--;
		}
		else if (buf == old.c_cc[VKILL]){
			for (int i = 0; i<c; i++){
				printf("\b");
				str[s][i] = 0;
			}
			printf("\033[K");
			c = 0;
			il = 0;
		}
		else if (buf == old.c_cc[VWERASE]){
			if (c !=0 ){
				for(int i = 0; i < size_w[count_w]; i++)
					printf("\b");
				printf("\033[K");
				c -= size_w[count_w];
				size_w[count_w] = 0;
				count_w--;
				il = 0;
				fl = 1;
			}
		}
		else if (buf == old.c_cc[VEOF]){
			if(c==0)
				break;
		}
		else if (buf == old.c_cc[VINTR] || buf == old.c_cc[VQUIT] || buf == old.c_cc[VSTOP] || buf == old.c_cc[VSTART] || buf == old.c_cc[VSUSP] || buf == old.c_cc[VDISCARD] || buf == old.c_cc[VLNEXT] || buf == old.c_cc[VREPRINT])
			printf("\a");
		else{
			if (buf == ' '){
				fl = 1;
				size_w[count_w]++;
			}
			else{
				if (fl == 1){
						count_w++;
						size_w = realloc(size_w, sizeof(int) * (count_w+1));
						size_w[count_w] = 0;
						il = 0;
						fl = 0;
					}
				size_w[count_w]++;
			}
			if(c == 40){
				if (il == 40){
					printf("\nERROR\n");
					break;
				}
				s++;
				str = (int**)realloc(str, sizeof(int*) * (s+1));
				str[s] = (int*)malloc(sizeof(int) * 40);
				for(int i = 0; i < il; i++)
					printf("\b");
				printf("\033[K");
				printf("\n");
				for(int i = 0; i < il; i++){
					str[s][i] = last[i];
					printf("%c", last[i]);
				}
				c = il;
			}
			str[s][c] = buf;
			last[il] = buf;
			il++;
			c++;
			printf("%c", buf);
		}
	}
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	f = tcsetattr(0, TCSANOW, &old);
	return 0;
}