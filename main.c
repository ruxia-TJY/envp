/*
Copyright (c) 2023 JiayuTu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "include/tColorPC.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

#define VERSION "0.0.0.1"

typedef struct env{
    char *key;
    char *value;
    struct env *next;
}Env;

static struct option long_options[] = {
        {"color",no_argument,NULL,'c'},
        {"help",no_argument,NULL,'h'},
        {"split",no_argument,NULL,'s'},
        {"version",no_argument,NULL,'v'}
};

extern char **environ;


Env *create(char *str);
Env *add(Env *pH,Env *new);

void printKEYVALUE(Env *env,BOOL ColorFlag,BOOL SplitFlag);
int getlen(char *str);
void Usage();

int main(int argc,char *argv[]) {
    BOOL ColorFlag = FALSE;
    BOOL SplitFlag = FALSE;


    int MoreFlag = 0;
    char *MoreArg = argv[1];

    int c;
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "chsv",
                            long_options, &option_index)) != -1) {
        switch (c) {
            case 'c':
                ColorFlag = TRUE;
                break;
            case 's':
                SplitFlag = TRUE;
                break;
            case 'h':
                Usage();
                return 0;
            case 'v':
                printf(VERSION "\n");
                return 0;
            default:
                fprintf(stderr, "Error: invalid option");
                return 0;
        }
    }

    MoreFlag = argc - ColorFlag - SplitFlag - 1;


    char **envstr = environ;

    // can not get environ
    if (getlen(*envstr) == 0) {
        fprintf(stderr, "Error: can not get environment\n");
        return 0;
    }

    int KEY_len = 1;

    Env *head = create(*envstr);
    *envstr++;

    while (*envstr) {
        add(head, create(*envstr));
        *envstr++;
        KEY_len++;
    }


    Env *temp = head;

    if (MoreFlag) {
        if (!strcmp(temp->key, MoreArg)) {
            printf("------");
            printKEYVALUE(temp, ColorFlag, SplitFlag);
            return 0;
        }

    } else {
        printKEYVALUE(temp, ColorFlag, SplitFlag);
    }

    while ((temp = temp->next) != NULL) {
        if (MoreFlag) {
            if (!strcmp(temp->key, MoreArg)) {
                printKEYVALUE(temp, ColorFlag, SplitFlag);
                return 0;
            }
        } else {
            printKEYVALUE(temp, ColorFlag, SplitFlag);
        }
    }
    return 0;

}

void printKEYVALUE(Env *env,BOOL ColorFlag,BOOL SplitFlag)
{
    if(ColorFlag)printf(TCOLORPC_P_FR_GREEN);
    printf("%s",env->key);
    if(ColorFlag)printf(TCOLORPC_P_FR_ORANGE);
    printf("=");

    if(ColorFlag)printf(TCOLORPC_P_NORMAL);
    if(SplitFlag){
        char *temp = strtok(env->value,":");
        if(temp == NULL){
            printf("\n");
            return;
        }
        printf("%s\n",temp);

        while (temp){
            temp = strtok(NULL,":");
            if(temp)
                printf("\t%s\n",temp);
        }
    }
    else
        printf("%s\n",env->value);

}



int getlen(char *str)
{
    int len = 0;

    while (*str){
        *str++;
        len++;
    }
    return len;
}


Env *add(Env *pH,Env *new)
{
    Env *p = pH;
    while (NULL != p->next){
        p = p->next;
    }
    p->next = new;
}

Env* create(char *str)
{
    Env *node = NULL;
    node = (Env *) malloc(sizeof (Env));

    if(node == NULL){
        printf("malloc fair!\n");
    }

    char *temp = str;
    char *key;
    char *value;
    key = strtok_r(temp,"=",&value);
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

void Usage()
{
    fprintf(stdout,"Usage: [OPTION]\n");
    fprintf(stdout,"\t-c, --color\t\tcolorize the output\n");

    fprintf(stdout,"\t-h, --help\t\tshow usage\n");
    fprintf(stdout,"\t-s, --split\t\tsplit VALUE 1 in line\n");
    fprintf(stdout,"\t-v, --version\t\tshow version\n");
    fprintf(stdout,"ver:" VERSION " copyright JiayuTu<ruxia.tjy@qq.com>\nthanks for use!\n");

}