#include <stdio.h>
#include <string.h>
#include "func.h"
#include <stdbool.h>
#include <regex.h>

bool suf(char *input,char *str) {
	FILE *input_file = fopen(input,"r+");
	if (input_file==NULL)
	{
		perror("Ошибка при открытии исходного файла\n");
		return false;
	}
	fseek(input_file,0,SEEK_END);
	size_t size = ftell(input_file);
	rewind(input_file);
	char text[size+1];
	fread(text,1,size,input_file);
	text[size]=0;
	freopen(input,"w",input_file);
	if (input_file==NULL)
	{
		perror("Ошибка открытия исходного файла\n");
		return false;
	}
	char *str_ptr = text;
	int len = strlen(text);
	for (int i = 0;i<len-1;i++)
	{
		if (text[i+1]=='\n')
		{
			text[i+1]=0;
			fputs(str_ptr,input_file);
			fputs(str,input_file);
			fprintf(input_file,"%c",'\n');
			if (i+2!=len)
			{
				str_ptr = &text[i+2];
			}
		}
	}
	fclose(input_file);
	return true;
}

bool pref(char *input,char *str) {
        FILE *input_file = fopen(input,"r+");
        if (input_file==NULL)
        {
                perror("Ошибка при открытии исходного файла\n");
                return false;
        }
        fseek(input_file,0,SEEK_END);
        size_t size = ftell(input_file);
        rewind(input_file);
        char text[size+1];
        fread(text,1,size,input_file);
        text[size]=0;
        freopen(input,"w",input_file);
        if (input_file==NULL)
        {
                perror("Ошибка открытия исходного файла\n");
                return false;
        }
        char *str_ptr = text;
        int len = strlen(text);
        for (int i = 0;i<len-1;i++)
        {
                if (text[i+1]=='\n')
                {
                        text[i+1]=0;
                        fputs(str,input_file);
			fputs(str_ptr,input_file);
                        fprintf(input_file,"%c",'\n');
                        if (i+2!=len)
                        {
                                str_ptr = &text[i+2];
                        }
                }
        }
	fclose(input_file);
        return true;
}

bool del(char *input,char *str) {
        FILE *input_file = fopen(input,"r+");
        if (input_file==NULL)
        {
                perror("Ошибка при открытии исходного файла\n");
                return false;
        }
        fseek(input_file,0,SEEK_END);
        size_t size = ftell(input_file);
        rewind(input_file);
        char text[size+1];
        fread(text,1,size,input_file);
        text[size]=0;
        freopen(input,"w",input_file);
        if (input_file==NULL)
        {
                perror("Ошибка открытия исходного файла\n");
                return false;
        }
        char *str_ptr = text;
	regex_t regex;
        if (regcomp(&regex,str,REG_EXTENDED))
	{
		perror("Неправильно введено регулярное выражение\n");
		return false;
	}
	regmatch_t matches[1];
	while (regexec(&regex,str_ptr,1,matches,0)==0)
	{
		bool per = false;
		str_ptr[matches[0].rm_so]=0;
		if (*str_ptr == text[0] || *(str_ptr-1)=='\n')
		{
			per = true;
		}
		fputs(str_ptr,input_file);
		str_ptr=str_ptr+matches[0].rm_eo;
		if (*str_ptr=='\n' && per==true)
		{
			str_ptr++;
		}
	}
	fputs(str_ptr,input_file);
	regfree(&regex);
	fclose(input_file);
        return true;
}

int correct_replace(char *str) {
	int cnt = 0;
	int len = strlen(str);
	for (int i = 0;i<len;i++)
	{
		if (str[i]=='/')
		{
			cnt++;
		}
		if (i==len-1 && str[i]!='/')
		{
			cnt=0;
		}
	}
	if (str[0]=='s' && str[1]=='/')
	{
		return cnt;
	}
	return 0;
}

bool repl(char *input,char *str) {
	char *new = strstr(str,"/")+1;
	new[strlen(new)-1]=0;
	int len = strlen(str);
	for (int i = 0;i<len;i++)
	{
		if (str[i]=='/')
		{
			str[i]=0;
		}
	}
        FILE *input_file = fopen(input,"r+");
        if (input_file==NULL)
        {
                perror("Ошибка при открытии исходного файла\n");
                return false;
        }
        fseek(input_file,0,SEEK_END);
        size_t size = ftell(input_file);
        rewind(input_file);
        char text[size+1];
        fread(text,1,size,input_file);
        text[size]=0;
        freopen(input,"w",input_file);
        if (input_file==NULL)
        {
                perror("Ошибка открытия исходного файла\n");
                return false;
        }
        char *str_ptr = text;
        regex_t regex;
        if (regcomp(&regex,str,REG_EXTENDED))
        {
                perror("Неправильно введено регулярное выражение\n");
                return false;
        }
        regmatch_t matches[1];
        while (regexec(&regex,str_ptr,1,matches,0)==0)
        {
                str_ptr[matches[0].rm_so]=0;
                fputs(str_ptr,input_file);
		fputs(new,input_file);
                str_ptr=str_ptr+matches[0].rm_eo;
        }
        fputs(str_ptr,input_file);
	regfree(&regex);
	fclose(input_file);
        return true;
}
