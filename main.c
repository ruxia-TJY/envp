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
#include <getopt.h>
#include "include/tColorPC.h"

#define BOOL int
#define TRUE 1
#define FALSE 0

#define VERSION "0.0.0.3"
#define AUTHOR "JiayuTu<ruxia.tjy@qq.com>"

#define print_opt_help(opt_index,help_str) \
    do{                                    \
		printf("\t--%s\t-%c\t%s", long_options[opt_index].name, (char)long_options[opt_index].val, help_str); \
	} while (0)

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

static Env *create_node(char *str);
static void *add_node(Env *pH, Env *new);
static void free_Env(Env *head);
static Env *find_node(Env *head,char *name);

static void print_node(Env *env, BOOL ColorFlag, BOOL SplitFlag);
static int get_len(char *str);

static void Usage();

int main(int argc,char *argv[]) {
    BOOL color_flag = FALSE;
    BOOL split_flag = FALSE;

    // just hope one Key, such as $PATH
    //      envp PATH -s -c
    // print_all_flag_all_0 = argc - color_flag - split_flag - 1
    // 1: only print PATH
    // 0: print All
    int print_all_flag_all_0;

    int c;
    int option_index = 0;
    while ((c = getopt_long(argc, argv, "chsv",
                            long_options, &option_index)) != -1) {
        switch (c) {
            case 'c':
                color_flag = TRUE;
                break;
            case 's':
                split_flag = TRUE;
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

    print_all_flag_all_0 = argc - color_flag - split_flag - 1;
    int index_print_all_flag = argc - 1;


    char **envstr = environ;

    // can not get environ
    if (get_len(*envstr) == 0) {
        fprintf(stderr, "Error: can not get environment\n");
        return 0;
    }

    Env *head = create_node(*envstr);
    *envstr++;

    while (*envstr) {
        add_node(head, create_node(*envstr));
        *envstr++;
    }

    if (print_all_flag_all_0){
        Env *temp = find_node(head,argv[index_print_all_flag]);

        if (temp != NULL){
            print_node(temp, color_flag, split_flag);
        } else{
            printf("%s not found!\n",argv[index_print_all_flag]);
        }
    } else{
        print_node(head,color_flag,split_flag);
        while (NULL != (head = head->next)){
            print_node(head,color_flag,split_flag);
        }
    }

    free_Env(head);
    return 0;
}

static void print_node(Env *env, BOOL ColorFlag, BOOL SplitFlag)
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

static int get_len(char *str)
{
    int len = 0;

    while (*str){
        *str++;
        len++;
    }
    return len;
}

static void *add_node(Env *pH, Env *new)
{
    Env *p = pH;
    while (NULL != p->next){
        p = p->next;
    }
    p->next = new;
}

static Env* create_node(char *str)
{
    Env *node = NULL;
    node = (Env *) malloc(sizeof (Env));

    if(NULL == node){
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

static Env *find_node(Env *head,char *name)
{
    if(!strcmp(head->key,name))return head;

    while (NULL != (head = head->next)){
        if(!strcmp(head->key,name))return head;
    }
    return NULL;
}

static void free_Env(Env *head)
{
    Env *tmp;
    while (NULL != head){
        tmp = head;
        head = head->next;
        free(tmp);
        tmp = NULL;
    }
}

static void Usage()
{
    printf("\nUsage:\n");
    print_opt_help(0,"colorize the output\n");
    print_opt_help(1,"show the help\n");
    print_opt_help(2,"split VALUE 1 in line\n");
    print_opt_help(3,"show Version\n");
    printf("\n" "ver:" VERSION "  copyright " AUTHOR "\n");

}