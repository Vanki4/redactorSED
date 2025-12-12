#include <stdio.h>
#include <string.h>
#include "func.h"

int main(int argc,char **argv) {
	if (argc!=3)
	{
		printf("Некоректное число аргументов\n");
		return -1;
	}
	char *com;
	if ((com=strstr(argv[2],"s/$/"))!=NULL)
	{
		com=com+4;
		com[strlen(com)-1]=0;
		if (!suf(argv[1],com))
		{
			return -2;
		}
	}
	else if ((com=strstr(argv[2],"s/^/"))!=NULL)
        {       
                com=com+4;
                com[strlen(com)-1]=0;
                if (!pref(argv[1],com))
                {       
                        return -2;
                }
        }
	else if (strstr(argv[2],"/d")!=NULL)
	{
		com=strstr(argv[2],"/")+1;
		com[strlen(com)-2]=0;
		if (!del(argv[1],com))
		{
			return -2;
		}
	}
	else if (correct_replace(argv[2])==3)
	{
		com=strstr(argv[2],"s/");
		com=com+2;
		if (!repl(argv[1],com))
		{
			return -2;
		}
	}
	else 
	{
		printf("Введена некоректная команда\n");
		return -3;
	} 
	return 0;
}
