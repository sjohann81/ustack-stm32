#define NULL			((void *)0)
#define USED			1
#define TRUE			1
#define FALSE			0
#define isprint(c)		(' '<=(c)&&(c)<='~')
#define isspace(c)		((c)==' '||(c)=='\t'||(c)=='\n'||(c)=='\r')
#define isdigit(c)		('0'<=(c)&&(c)<='9')
#define islower(c)		('a'<=(c)&&(c)<='z')
#define isupper(c)		('A'<=(c)&&(c)<='Z')
#define isalpha(c)		(islower(c)||isupper(c))
#define isalnum(c)		(isalpha(c)||isdigit(c))
#define min(a,b)		((a)<(b)?(a):(b))

char *strcpy(char *dst, char *src);
char *strncpy(char *s1, char *s2, int32_t n);
char *strcat(char *dst, char *src);
char *strncat(char *s1, char *s2, int32_t n);
int32_t strcmp(char *s1, char *s2);
int32_t strncmp(char *s1, char *s2, int32_t n);
char *strstr(char *string, char *find);
int32_t strlen(char *s);
char *strchr(char *s, int32_t c);
char *strpbrk(char *str, char *set);
char *strsep(char **pp, char *delim);
char *strtok(char *s, char *delim);
int32_t strtol(char *s, char **end, int32_t base);
int32_t atoi(char *s);
void *memcpy(void *dst, void *src, uint32_t n);
void *memmove(void *dst, void *src, uint32_t n);
int32_t memcmp(void *cs, void *ct, uint32_t n);
void *memset(void *s, int32_t c, uint32_t n);
int32_t abs(int32_t n);
int32_t random(void);
void srand(uint32_t seed);
int32_t puts(char *str);
char *gets(char *s);
char *getline(char *s);
int32_t printf(const char *fmt, ...);
int32_t sprintf(char *out, const char *fmt, ...);


