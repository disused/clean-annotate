#include <stdio.h>

int main(int argc, const char *argv[])
{
    char buf[1024];
	FILE *fp;
	fp = fopen("1.txt","r");
	fgets(buf,1024,fp);
    printf("%s\n",buf);
    return 0;
}
