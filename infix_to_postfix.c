#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260

int tokenval;
int lineno;

struct entry {
    char lexptr[BSIZE];
    int token;
};

struct entry symtable[BSIZE];

int lookup(char s[]);
int insert(char s[], int tok);

int lexan() {
    int t;
    char lexbuf[BSIZE];
    int b = 0;

    while (1) {
        t = getchar();
        if (t == ' ' || t == '\t') {
            continue;
        } else if (t == '\n') {
            lineno++;
        } else if (isdigit(t)) {
            ungetc(t, stdin);
            scanf("%d", &tokenval);
            return NUM;
        } else if (isalpha(t)) {
            while (isalnum(t)) {
                lexbuf[b++] = t;
                if (b >= BSIZE) {
                    fprintf(stderr, "compiler error");
                    exit(1);
                }
                t = getchar();
            }
            lexbuf[b] = EOS;
            if (t != EOF) {
                ungetc(t, stdin);
            }
            int p = lookup(lexbuf);
            if (p == 0) {
                if (strcmp(lexbuf, "div") == 0)
                    p = insert(lexbuf, DIV);
                else if (strcmp(lexbuf, "mod") == 0)
                    p = insert(lexbuf, MOD);
                else
                    p = insert(lexbuf, ID);
            }
            tokenval = p;
            return symtable[p].token;
        } else if (t == EOF) {
            return DONE;
        } else if (t == '/' || t == '%' || t == '(' || t == ')' || t == ';' || t == '+' || t == '-' || t == '*') {
            return t;
        } else {
            fprintf(stderr, "Syntax error");
            exit(1);
        }
    }
}

void parse();

void expr();
void term();
void factor();
void emit(int t, int tval);
void match(int t);
void error(char *m);

int lookahead;

void parse() {
    lookahead = lexan();
    while (lookahead != DONE) {
        expr();
        match(';');
    }
}

void expr() {
    int t;
    term();
    while (1) {
        switch (lookahead) {
            case '+':
            case '-':
                t = lookahead;
                match(lookahead);
                term();
                emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}

void term() {
    int t;
    factor();
    while (1) {
        switch (lookahead) {
            case '*':
            case '/':
            case DIV:
            case MOD:
                t = lookahead;
                match(lookahead);
                factor();
                emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}

void factor() {
    switch (lookahead) {
        case '(':
            match('(');
            expr();
            match(')');
            break;
        case NUM:
            emit(NUM, tokenval);
            match(NUM);
            break;
        case ID:
            emit(ID, tokenval);
            match(ID);
            break;
        default:
            error("Syntax error");
    }
}

void match(int t) {
    if (lookahead == t) {
        lookahead = lexan();
    } else {
        error("Syntax error");
    }
}

void emit(int t, int tval) {
    switch (t) {
        case '+':
        case '-':
        case '*':
        case '/':
            printf("%c", t);
            break;
        case DIV:
            printf("DIV");
            break;
        case MOD:
            printf("MOD");
            break;
        case NUM:
            printf("%d", tval);
            break;
        case ID:
            printf("%s", symtable[tval].lexptr);
            break;
        default:
            printf("token %d, tokenval %d\n", t, tval);
    }
}

int lookup(char s[]) {
    int p;
    for (p = BSIZE; p > 0; p--) {
        if (strcmp(symtable[p].lexptr, s) == 0) {
            return p;
        }
    }
    return 0;
}

int insert(char s[], int tok) {
    int len = strlen(s);
    if (len + 1 >= BSIZE) {
        fprintf(stderr, "lexemes array full");
        exit(1);
    }
    strcpy(symtable[len + 1].lexptr, s);
    symtable[len + 1].token = tok;
    return len + 1;
}

void error(char *m) {
    fprintf(stderr, "line %d: %s\n", lineno, m);
    exit(1);
}

int main() {
    lineno = 1;
    parse();
    return 0;
}
