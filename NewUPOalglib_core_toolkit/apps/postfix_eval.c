/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/postfix_eval.c
 *
 * \brief An application to evaluate postfix mathematical expressions.
 *
 * \author Your Name
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include "postfix_eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/stack.h>


#define MAX_LINE_LEN 256

/*TO STUDENTS: Complete the body of eval_postfix:
    1. The type of operands and operations result is long int
    2. Parameter expr is a string containing the postfix expression
    3. Valid (binary) operators: +; -; *; =; %; ^
    4. Numbers and operators are separated by spaces
    5. Only nonnegative integer numbers: 0, 19, . . .
  
    Hint: use isdigit() to check if a character is a digit, and
          sscanf() to read numbers from a string as long int (format "%ld")
    
    6. Parameter res is the result of the evaluation of the postfix expression
    7. Returns 1 if expr is well-formed, 0 otherwise
*/

int eval_postfix(const char *expr, long *res)
{
    const char *ptr=expr;
    char line[MAX_LINE_LEN];
    upo_stack_t stack=upo_stack_create();
    int i=0;
    while(sscanf(ptr, "%s", line)==1)
    {
        ptr+=strlen(line);
        //printf("SIMBOLO: %s\n", line);
        if(isdigit(line[0]))
        {
            long symbol[10];
            symbol[i]=atol(line);
            //printf("SIMBOLO: %ld\n", symbol);
            upo_stack_push(stack, &symbol[i]);
            i++;
        }
        else
        {
            if(upo_stack_size(stack)==0)
            {
                upo_stack_destroy(stack, 0);
                return 0;
            }
                long operator2 = *((long*) upo_stack_top(stack));
                upo_stack_pop(stack, 0);
                //printf("Operatore 2: %ld\n", operator2);
                long operator1 = *((long*) upo_stack_top(stack));
                upo_stack_pop(stack, 0);
                //printf("Operatore 1: %ld\n", operator1);
                long result;

            switch (line[0])
            {
            case '+':
                result=operator1+operator2;
                break;
            
            case '-':
                result=operator1-operator2;
                break;
            
            case '*':
                result=operator1*operator2;
                break;

            case '/':
                if(operator2==0)
                {
                    upo_stack_destroy(stack, 0);
                    return 0;
                }
                result=operator1/operator2;
                break;

            case '%':
                if(operator2==0)
                {
                    upo_stack_destroy(stack, 0);
                    return 0;
                }
                result=operator1%operator2;
                break;

            case '^':
                result=(long)pow(operator1, operator2);
                break;

            default:
                upo_stack_destroy(stack, 0);
                return 0;
            }
            //printf("RISULTATO: %ld\n", result);
            upo_stack_push(stack, &result);
            //printf("TOP3: %ld\n", *(long*)upo_stack_top(stack));
        }
        while(ptr && isspace(*ptr)) ptr++;
        
    }
    if(upo_stack_size(stack)!=1)
        {
            upo_stack_destroy(stack, 0);
            return 0;
        }
    
    *res=*(long*)upo_stack_top(stack);
    upo_stack_destroy(stack, 0);
    return 1;
}

void eval_lines(FILE *fp)
{
    char line[MAX_LINE_LEN];

    while (fgets(line, sizeof(line), fp))
    {
        size_t slen = strlen(line);
        int ok = 0;
        long res = 0;
        char *res_str = NULL;
        long expect_res = 0;

        /* Strips the terminating newline (if any) */
        if (slen > 0 && line[slen-1] == '\n')
        {
            line[slen-1] = '\0';
            --slen;
        }

        /* Checks if we have the expected result. In this case the input line should be: <expr>, <result> */
        res_str = strstr(line, "=>");
        if (res_str != NULL)
        {
            line[res_str-line] = '\0';
            res_str += 2;
            expect_res = atol(res_str);
        }

        ok = eval_postfix(line, &res);
        if (ok)
        {
            if (res_str != NULL)
            {
                printf("Expression '%s' -> %ld (expected: %ld -> %s)\n", line, res, expect_res, (res == expect_res) ? "OK" : "KO");
            }
            else
            {
                printf("Expression '%s' -> %ld\n", line, res);
            }
        }
        else
        {
            printf("Expression '%s' -> Malformed\n", line);
        }
    }
}

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s -f [<filename>]\n", progname);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "-f <filename>: The full path name to the file containing strings (one for each line).\n"
                    "               If not given, strings are read from standard input.\n"
                    "               [default: standard input]\n");
    fprintf(stderr, "-h: Displays this message\n");
    fprintf(stderr, "-v: Enables output verbosity\n");
}


int main(int argc, char *argv[])
{
    char *opt_filename = NULL;
    int opt_help = 0;
    int opt_verbose = 0;
    int arg = 0;
    FILE *fp = NULL;

    for (arg = 1; arg < argc; ++arg)
    {
        if (!strcmp("-f", argv[arg]))
        {
            ++arg;
            if (arg >= argc)
            {
                fprintf(stderr, "ERROR: expected file name.\n");
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            opt_filename = argv[arg];
        }
        else if (!strcmp("-h", argv[arg]))
        {
            opt_help = 1;
        }
        else if (!strcmp("-v", argv[arg]))
        {
            opt_verbose = 1;
        }
    }

    if (opt_help)
    {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (opt_verbose)
    {
        printf("-- Options:\n");
        printf("* File name: %s\n", opt_filename ? opt_filename : "<not given>");
    }

 
    if (opt_filename != NULL)
    {
        fp = fopen(opt_filename, "r");
        if (fp == NULL)
        {
            perror("ERROR: cannot open input file");
            return EXIT_FAILURE;
        }
    }
    else
    {
        fp = stdin;
    }

    if (opt_verbose)
    {
        printf("-- Evaluating...\n");
    }

    eval_lines(fp);

    if (opt_filename != NULL)
    {
        fclose(fp);
    }

    return EXIT_SUCCESS;
}