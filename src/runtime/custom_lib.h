#ifndef CUSTOM_LIB_H
#define CUSTOM_LIB_H

char *__strdup(char *s)
{
	char *dupS = (char*)malloc(strlen(s) * sizeof(char));
	strcpy(dupS,s);

	return dupS;
}


#endif
