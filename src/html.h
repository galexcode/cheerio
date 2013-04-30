#include "dom.h"

page * parseHTML(char *doc);
char * readattributes(char *doc, ilist *curr);
char * gettagtext(char *doc, page *dom);
char * gstrd(char **s, char d, char *data);
char * parsetag(char *doc, page *dom);
char * skiptext(char *doc, char d);
void storeattr(attr **a, char *key, char *value);

static const int elements = 116;
static const char *element[] = {
"a",
"abbr",
"acrnym",
"address",
"applet",
"area",
"b",
"base",
"basefont",
"bdo",
"big",
"blockquote",
"body",
"br",
"button",
"canvas",
"caption",
"center",
"cite",
"code",
"col",
"colgroup",
"command",
"datalist",
"dd",
"del",
"details",
"dfn",
"dialog",
"dir",
"div",
"dl",
"dt",
"em",
"embed",
"fieldset",
"figcaption",
"figure",
"font",
"footer",
"form",
"frame",
"frameset",
"h1",
"h2",
"h3",
"h4",
"h5",
"h6",
"head",
"hgroup",
"hr",
"html",
"i",
"iframe",
"img",
"input",
"ins",
"kbd",
"keygen",
"label",
"legend",
"li",
"link",
"map",
"mark",
"menu",
"meta",
"meter",
"nav",
"noframes",
"noscript",
"object",
"ol",
"optgroup",
"option",
"output",
"p",
"param",
"pre",
"progress",
"q",
"rp",
"rt",
"ruby",
"s",
"samp",
"script",
"section",
"select",
"small",
"source",
"span",
"strike",
"strong",
"style",
"sub",
"summary",
"sup",
"table",
"tbody",
"td",
"textarea",
"tfoot",
"th",
"thead",
"time",
"title",
"tr",
"track",
"tt",
"u",
"ul",
"var",
"video",
"wbr"
};
