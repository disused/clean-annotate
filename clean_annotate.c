#include <stdio.h>
#include <string.h>

enum state_e{TEXT,
		A_ANNO,//
		B_ANNO,/*....*/
		STR};

int clean_annotate(FILE *dest,FILE *src)
{
	enum state_e state = TEXT;
	int c = -1;
	int b = -1;

	c=fgetc(src);
	if(c == '/')
	{
		c=fgetc(src);
		if(c == '*')
			state = B_ANNO;
		else if(c == '/')
			state = A_ANNO;
		else
		{
			printf("Source file format is wrong\n");
			return -1;
		}	
	}
	else
	{
		state = TEXT;
		fputc(c,dest);
	}

	while((c=fgetc(src)) != EOF)
	{
		switch(state)
		{
			case TEXT:				
				if(c == '/')
			 	{
					b=c;
					c=fgetc(src);
					if(c == '/')
						state = A_ANNO;
					else if(c == '*')
						state = B_ANNO;
					else if(c == '"')
					{
						fputc(b,dest);
						fputc(c,dest);
						state = STR;
					}
					else
					{
						fputc(c,dest);
						state = TEXT;
					}
				}
				else if(c == '"')
				{
					fputc(c,dest);
					state = STR;
				}
				else
				{
					fputc(c,dest);
				}
				break;
			case A_ANNO:
				if(c == '\n')
					state = TEXT;
				break;
			case B_ANNO:
				if(c == '*')
				{
					b=c;
					c=fgetc(src);
					if(c == '/')
						state = TEXT;
				}
				break;
			case STR:
				if(c == '"')
				{
					fputc(c,dest);
					state = TEXT;
				}
				else
				{
					fputc(c,dest);
					state = STR;
				}
				break;
		}
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	FILE *fp_dest = NULL;
	FILE *fp_src = NULL;
	if(argc < 3)
	{
		printf("Please input source file name and dest file name\n");
		return -1;
	}

	fp_dest = fopen(argv[2],"w");
	fp_src = fopen(argv[1],"r");

	if(fp_dest == NULL)
	{
		printf("dest file open failure\n");
		return -1;
	}
	if(fp_src == NULL)
	{
		printf("src file open failure\n");
		return -1;
	}
	clean_annotate(fp_dest,fp_src);

	return 0;
}
