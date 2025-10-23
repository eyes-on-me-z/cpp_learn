#include "process.h"

void ProcessOn()
{
    char style[S_NUM] = {'-', '.', '#', '>', '+'};
    const char label[] = {'|', '/', '-', '\\'};
    char bar[NUM];
    memset(bar, '\0', NUM);

    int cnt = 0;
    while(cnt <= 100)
    {
        printf("[%-100s] %d%% %c\r", bar, cnt, label[cnt % 4]);
	fflush(stdout);
	usleep(50000);
	bar[cnt] = style[N];
	cnt++;
    }

    printf("\n");
}
