#include <stdlib.h>
#include <stdio.h>
#include "html.h"

int main(int argc, char *argv[]) {
	FILE *fh = fopen(argv[1], "r");
	int fsz = 0;
	char *data;
	fseek(fh, 0L, SEEK_END);
	fsz = ftell(fh);
	data = (char *)malloc(sizeof(char)*fsz+1);
	fseek(fh, 0L, SEEK_SET);
	fread(data, fsz, 1, fh);
	data[fsz] = '\0';
	fclose(fh);
	page *dom = parseHTML(data);
	dom->curr = dom->il;
	for(;dom->curr != NULL; dom->curr = dom->curr->nitem) {
		if(dom->curr->type >= 0 && dom->curr->type < elements) {
			printf("%s\n", element[dom->curr->type]);
			if(dom->curr->a != NULL) {
				if(dom->curr->a->innerhtml != NULL)
					printf("\tINNERHTML:%s\n", dom->curr->a->innerhtml);
				if(dom->curr->a->innerhtml != NULL)
					printf("\tCLASS:%s\n", dom->curr->a->class);
			}
			printf("\n");
		}
	}
	return 0;
}
