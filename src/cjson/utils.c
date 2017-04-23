/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/01/2017 06:18:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kevin (WangWei), kevin.wang2004@hotmail.com
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../calcurse.h"

static cJSON *mjson_root = NULL;


	static 
void write_to_file(char* buf)
{
	FILE* fd = NULL;
	fd = fopen(path_abook,"w+");
	int len = strlen(buf);

	if ( fd != NULL )
	{
		fwrite(buf,1,len,fd);
		fclose(fd);
	}
}

void cjson_sync_disk()
{
	char *out = cJSON_Print(mjson_root);	
	write_to_file(out);
	free(out);
}

void cjson_insert_element(ABOOK* ab)
{
	cJSON *element;
	cJSON_AddItemToObject(mjson_root, "element",element=cJSON_CreateObject());
	cJSON_AddStringToObject(element,"姓名",ab->name);
	cJSON_AddStringToObject(element,"E-mail",ab->email);
}

void init_json_module()
{
	mjson_root = cJSON_CreateObject();

	cJSON_AddItemToObject(mjson_root, "version", cJSON_CreateString("V1.0.0"));
	cJSON_AddStringToObject(mjson_root, "title", "通讯录");

}

void release_json_module() 
{
	if ( NULL != mjson_root )
	{
		cJSON_Delete(mjson_root);
	}
}
