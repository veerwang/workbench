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
static cJSON *mjson_read_root = NULL;


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

	static
int get_file_length()
{
	FILE* fd = NULL;
	fd = fopen(path_abook,"r");

	if ( fd != NULL )
	{
		fseek(fd,0L,SEEK_END);
		int size = ftell(fd);
		fclose(fd);
		return size;
	}
	return 0;
}

	static
void read_from_file(char* buf,int len)
{
	FILE* fd = NULL;
	fd = fopen(path_abook,"r");

	if ( fd != NULL )
	{
		fread(buf,len,1,fd);
		fclose(fd);
	}
}

/*
 * 将json数据保存到磁盘中 
 */
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

/*
 * 将json数据从磁盘中读取
 */
void cjson_parse_disk()
{
	int length = get_file_length();
	char *raw = xmalloc(length);
	read_from_file(raw,length);

	mjson_read_root = cJSON_Parse(raw);
	printf("%s: %s\n",mjson_read_root->child->string,mjson_read_root->child->valuestring);
	
	xfree(raw);
}

