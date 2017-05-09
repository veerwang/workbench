/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/01/2017 10:24:38 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *        Company:  LiLin-Tech
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cJSON.h"

void write_to_file(char* buf)
{
	FILE* fd = NULL;
	fd = fopen("computer_config","w+");
	int len = strlen(buf);

	if ( fd != NULL )
	{
		fwrite(buf,1,len,fd);
		fclose(fd);
	}
}

void read_from_file(char *buf)
{
	FILE* fd = NULL;
	fd = fopen("computer_config","r+");

	if ( fd != NULL )
	{
		fread(buf,1,1024,fd);
		fclose(fd);
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	void	
main ( int argc, char *argv[] )
{
	printf("JSON program Test\n");
	printf("------------------------\n");

	cJSON *root;
	cJSON *fmt;
	char* out;
	root = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "name", cJSON_CreateString("计算机品牌"));
	cJSON_AddStringToObject(root, "SN", "101010296555");
	cJSON_AddItemToObject(root, "fmt", fmt=cJSON_CreateObject());
	cJSON_AddNumberToObject(fmt, "width", 1920);
	cJSON_AddNumberToObject(fmt, "height", 1080);

	out=cJSON_Print(root);	
	cJSON_Delete(root);

	write_to_file(out);

	free(out);

	char buf[1024];
	read_from_file(buf);
	printf("%s\n",buf);

	printf("------------------------\n");

	cJSON *nroot;
	nroot = cJSON_Parse(buf);

	if (!nroot) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else {
		printf("type: %d\n",nroot->child->type);
		printf("%s: %s\n",nroot->child->string,nroot->child->valuestring);

		printf("type: %d\n",nroot->child->next->type);
		printf("%s: %s\n",nroot->child->next->string,nroot->child->next->valuestring);




		cJSON_Delete(nroot);
	}
}				/* ----------  end of function main  ---------- */
