#include <ctype.h>
#include <string.h>
#include <stdlib.h>
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
	int c;

	if(*doc == '<') {
		doc++;
		dom->curr->nitem = (ilist *)malloc(sizeof(ilist));
		dom->curr = dom->curr->nitem;
		for(c = 0; *doc != '>' || !*doc; doc++, c++) {
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
				if((tdoc = readattributes(doc, dom->curr)) != NULL)
					doc = tdoc;
					doc = gettagtext(doc, dom);
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
		return NULL;

	char *data;
	char *attr;

	doc++;
	for(; *doc != '>' || !*doc; doc++) {
		if(*doc != ' ') {
			doc = gstrd(attr, '=', doc);
			doc+=2;
			doc = gstrd(data, '"', doc);
			storeattr(curr->a, attr, data);
			free(attr);
			free(data);
		}
	}
	return doc;
}

char * gettagtext(char *doc, page *dom) {
	ilist tmp = {.type = dom->curr->type};
	doc = gstrd(dom->curr->a->innerhtml, '<', doc);
	doc++;
	if(*doc != '/') {
		doc = parsetag(doc, dom); //fucking recurse, uhgggg!!!!	
		if(*doc != '<') {
			dom->curr->nitem = (ilist *)malloc(sizeof(ilist));
			dom->curr = dom->curr->nitem;
			dom->curr->type = tmp.type;
			dom->curr->a = (attr *)malloc(sizeof(attr));
			doc = gettagtext(doc, dom);
			return doc;
		}
	}
	doc += strlen(element[dom->curr->type])+1;
	return doc;
}

void storeattr(attr *a, char *key, char *value) {
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
	} else if(strcmp(key, "title") == 0) {
	}
}

/*
 * Counts characters until the specified delimiter d. Then mallocs
 * space needed and assigns s the pointer. Increments the data pointer.
 * Returns the characters put in s.
 */
char * gstrd(char *s, char d, char *data) {
	int datasize = 0;
	int c;
	for(; *data != d || !*data; data++) {
		datasize++;
		if(*data == '\n')
			datasize--;
	}
	datasize--;
	s = (char *)malloc(sizeof(char)*datasize+1);
	data -= datasize;
	if(datasize > 0) {
		for(c = 0; *data != d || !*data; data++, c++) {
			if(*data != '\n')
				s[c] = tolower(*data);
		}
	} else {
		s[0] = '\0';
	}

	return data;
}

