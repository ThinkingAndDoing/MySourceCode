
#ifndef _FILTER_GLOBAL_H
#define _FILTER_GLOBAL_H

int  GetFirstStr(char *&table, char *s, int length);
int  GetFirstNStr(char *&table, char *s, int length, int n);
void GapN(char *&s, int n);
void FilterNull(char *&p, bool b);
void CountStr(char *p, int &col);
int  CountDateLines(char *ptable, char *pkey, int skip, int linemark);
void DeleteChar(char s[], char ch);
bool IsNumberStr(char *s);

#endif