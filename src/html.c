#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "html.h"

page * parseHTML(char *doc) {
	page *dom = (page *)malloc(sizeof(page));
	dom->il =  (ilist *)malloc(sizeof(ilist));
	dom->curr = dom->il;

	while(*doc) {
		doc = parsetag(doc, dom);
		doc++;
	}

	return dom;
}

char * parsetag(char *doc, page *dom) {
	char tag[12];
	char *tdoc = NULL;
	unsigned int c = 0;

	if(*doc == '<') {
		doc++;
		dom->curr->nitem = (ilist *)malloc(sizeof(ilist));
		dom->curr = dom->curr->nitem;
		for(c = 0; *doc != '>' && *doc != ' '; doc++, c++) {
			if(c >= 11)
				break; //encountered fucked up tag, skip
			tag[c] = tolower(*doc);
			if(tag[c] == '/') {
				break;
			}
		}
	}
	if(c < 11 && tag[0] != '\0') {
		tag[c] = '\0';
		for(c = 0; c < elements; c++) {
			if(strcmp(element[c], tag) == 0) {
				dom->curr->type = c;
				tdoc = readattributes(doc, dom->curr);
				if(tdoc != NULL) {
					doc = tdoc;
					doc = gettagtext(doc, dom);
				} else {
					doc++;
				}
				break;
			}
		}
	}

	return doc;
}

char * readattributes(char *doc, ilist *curr) {
	curr->a = (attr *)malloc(sizeof(attr));

	if(*doc == '/')
		return NULL;
	if(*doc == '>')
		return doc;

	char *data;
	char *attr;

	doc++;
	for(; *doc != '>' || !*doc; doc++) {
		if(*doc != ' ') {
			doc--;
			doc = gstrd(&attr, '=', doc);
			doc+=2;
			doc = gstrd(&data, '"', doc);
			storeattr(&curr->a, attr, data);
			free(attr);
			free(data);
		}
	}
	return doc;
}

char * gettagtext(char *doc, page *dom) {
	ilist tmp = {.type = dom->curr->type};
	doc = gstrd(&dom->curr->a->innerhtml, '<', doc);
	doc++;

	if(*doc != '/') {
		doc--;
		doc = parsetag(doc, dom);
		printf("tmp.type=%s\n", element[tmp.type]);
		dom->curr->nitem = (ilist *)malloc(sizeof(ilist));
		dom->curr = dom->curr->nitem;
		dom->curr->type = tmp.type;
		dom->curr->a = (attr *)malloc(sizeof(attr));
		doc = gettagtext(doc, dom);
		doc = skiptext(doc, '>');
	}

	if(*(doc-1) != '/')
		doc = skiptext(doc, '>');

	return doc;
}

char * skiptext(char *data, char d) {
	for(; *data != d; data++);
	return data;
}

void storeattr(attr **a, char *key, char *value) {
	printf("ATTR: %s\n", key);
	if(strcmp(key, "type") == 0) {
	} else if(strcmp(key, "src") == 0) {
	} else if(strcmp(key, "alt") == 0) {
	} else if(strcmp(key, "cellspacing") == 0) {
	} else if(strcmp(key, "rules") == 0) {
	} else if(strcmp(key, "border") == 0) {
	} else if(strcmp(key, "width") == 0) {
	} else if(strcmp(key, "height") == 0) {
	} else if(strcmp(key, "id") == 0) {
	} else if(strcmp(key, "class") == 0) {
		printf("CLASS: %s\n",value);
		(*a)->class = value;
	} else if(strcmp(key, "title") == 0) {
	}
}

/*
 * Counts characters until the specified delimiter d. Then mallocs
 * space needed and assigns s the pointer. Increments the data pointer.
 * Returns the characters put in s. Skips over newlines.
 */
char * gstrd(char **s, char d, char *data) {
	int datasize = 0;
	int c;

	if(*data == '\0')
		return data;

	for(; *data != d && *data != '\0'; data++) {
		datasize++;
		if(*data == '\n')
			datasize--;
	}

	if(datasize == 0) {
		**s = '\0';
		return data;
	}

	datasize--;
	*s = (char *)malloc(sizeof(char)*datasize+1);
	data -= datasize;

	for(c = 0; *data != d && *data != '\0'; data++, c++) {
		if(*data != '\n')
			*(*s+c) = *data;
	}
	*(*s+datasize) = '\0';

	return data;
}

