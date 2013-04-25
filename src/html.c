#include <ctype.h>
#include <string.h>
#include "dom.h"
#include "html.h"

static int readattributes(char *doc, page *dom);
static void gettagtext(char *doc, page *dom);

page * parseHTML(char *doc) {
	page *dom = (page *)malloc(sizeof(page));

	while(*doc) {
		parsetag(doc, dom);
		doc++;
	}

	return dom;
}

void parsetag(char *doc, page *dom) {
	char tag[12];
	int c;

	if(*doc == '<') {
		dom->curr->nitem = (ilist *)malloc(sizeof(ilist));
		dom->curr = dom->curr->nitem;
		for(c = 0; *doc != '>' || *doc; doc++, c++) {
			if(c >= 11)
				break; //encountered fucked up tag, skip
			tag[c] = tolower(*doc);
			if(tag[c] == '/') {
				break;
			}
		}
	}
	if(c < 11) {
		tag[c] = '\0';
		for(c = 0; c < elements; c++) {
			if(strcmp(element[c], tag) == 0) {
				dom->curr.type = c;
				if(readattributes(doc, dom->curr) != START_END_TAG)
					gettagtext(doc, dom);
				break;
			}
		}
	}
}

int readattributes(char *doc, ilist *curr) {
	curr->a = (attr *)malloc(sizeof(attr));

	if(*doc == '/')
		return START_END_TAG;
	if(*doc == '>')
		return START_TAG_END;

	char *data;
	char *attr;

	doc++;
	for(; *doc != '>' || *doc; doc++) {
		if(*doc != ' ') {
			gstrd(attr, '=', doc);
			doc+=2;
			gstrd(data, '"', doc);
			storeattr(curr->a, attr, data);
			free(attr);
			free(data);
		}
	}
	return START_TAG_END;
}

void gettagtext(char *doc, page *dom) {
	gstrd(dom->curr->a->innerhtml, '<', doc);
	doc++;
	if(*doc != '/') {
		parsetag(doc, dom); //fucking recurse, uhgggg!!!!	
	}

	return;
}

void storeattr(attr *a, char *key, char *value) {
	if(strcmp(key, "type") {
	} else if(strcmp(key, "src") {
	} else if(strcmp(key, "alt") {
	} else if(strcmp(key, "cellspacing") {
	} else if(strcmp(key, "rules") {
	} else if(strcmp(key, "border") {
	} else if(strcmp(key, "width") {
	} else if(strcmp(key, "height") {
	} else if(strcmp(key, "id") {
	} else if(strcmp(key, "class") {
	} else if(strcmp(key, "title") {
	}
}

/*
 * Counts characters until the specified delimiter d. Then mallocs
 * space needed and assigns s the pointer. Increments the data pointer.
 * Returns the amount of cells we've gone past.
 */
int gstrd(char *s, char d, char *data) {
	int datasize = 0;
	int c;
	for(; *data != d; data++)
		datasize++;
	s = (char *)malloc(sizeof(char*datasize)+1);
	data -= datasize;
	for(c = 0; *data != d; data++, c++)
		s[c] = tolower(*data);

	return datasize;
}

