#include <stdint.h>

typedef struct page page;
typedef struct item item;
typedef struct attr attr;

struct page {
	ilist *il;
	ilist *curr;
	//stylesheet *css;
};

struct ilist {
	int type; //refers to cell in *element[]
	double x, y, w, h;
	attr *a;
	ilist *nitem;
};

struct attr {
	char *type;
	char *href;
	char *src;
	char *alt;
	//char *style;
	int cellspacing;
	char *rules;
	int border;
	double *width;
	double *height;
	char *id;
	char *class;
	char *title;
	char *innerhtml;
};
