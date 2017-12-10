/*
* "Bixi" - Basic types management C89 library
*
*  Copyright (C) Alexey Shishkin 2017
*
*  This file is part of Project "Bixi".
*
*  Project "Bixi" is free software: you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  Project "Bixi" is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with Project "Bixi". If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libbixi.h>
#include "../test.h"
#include "../strings/tst_bxistring.h"

static void test_strings_bxi_strhash(void)
{
    printf("        checking: bxi_strhash\n");
    if (bxi_strhash("FNV") != 0xf5cfe2b9)
        test_failed();
}

static void test_strings_bxi_strshiftl(void)
{
    char shift[] = "abcdef";

    printf("        checking: bxi_strshiftl\n");
    if (bxi_strcmp(bxi_strshiftl(shift, 3), "def"))
        test_failed();
}

static void test_strings_bxi_strtriml(void)
{
    char triml[] = "   def";

    printf("        checking: bxi_strtriml\n");
    if (bxi_strcmp(bxi_strtriml(triml), "def"))
        test_failed();
}


static void test_strings_bxi_strtrimr(void)
{
    char trimr[] = "abc   ";

    printf("        checking: bxi_strtrimr\n");
    if (bxi_strcmp(bxi_strtrimr(trimr), "abc"))
        test_failed();
}

static void test_strings_bxi_strtrim(void)
{
    char trimc[] = "  cd  ";

    printf("        checking: bxi_strtrim\n");
    if (bxi_strcmp(bxi_strtrim(trimc), "cd"))
        test_failed();
}

static void test_strings_bxi_strlen(void)
{
    printf("        checking: bxi_strlen\n");
    if (bxi_strlen("abcdef") != 6)
        test_failed();
}

static void test_strings_bxi_strcmp(void)
{
    printf("        checking: bxi_strcmp\n");

    if (bxi_strcmp("abc", "abc"))
        test_failed();
    if (bxi_strcmp("", ""))
        test_failed();
    if (!bxi_strcmp("abcd", "abc"))
        test_failed();
}

static void test_strings_bxi_strprs(void)
{
    char   parsed[] = "  param1 param2 \"param 3\" \'param \"\\\' 4 \'";
    char * output[5];
    u32    count = 0;

    printf("        checking: bxi_strprs\n");
    if (bxi_strprs(parsed, &count, output) != 4)
        test_failed();

    if (count != 4)
        test_failed();

    if ((bxi_strcmp(output[0], "param1")) ||
        (bxi_strcmp(output[1], "param2")) ||
        (bxi_strcmp(output[2], "\"param 3\"")) ||
        (bxi_strcmp(output[3], "\'param \"\\\' 4 \'")))
        test_failed();
}

static void test_strings_bxi_strchr(void)
{
    printf("        checking: bxi_strchr\n");
    if (bxi_strcmp(bxi_strchr("abcdef", 'c'), "cdef"))
        test_failed();
}

static void test_strings_bxi_strcpy(void)
{
    char dst[10];
    char src[]   = "abcdef";

    printf("        checking: bxi_strcpy\n");

    bxi_strcpy(dst, src);
    if (bxi_strcmp(dst, src))
        test_failed();
}

static void test_strings_bxi_strstr(void)
{
    const char str[]   = "abcdef";
    const char sub[]   = "cd";

    printf("        checking: bxi_strstr\n");

    if (bxi_strcmp(bxi_strstr(str, sub), "cdef"))
        test_failed();
}

static void test_strings_bxi_is(void)
{
#   define TEST_ISCHAR(bxifunc, stdfunc)            \
    {                                               \
        i32 i;                                      \
        printf("        checking: %s\n", #bxifunc); \
                                                    \
        for (i = 0; i < 128; i++);                  \
        if (stdfunc(i) != bxifunc(i))               \
            test_failed();                          \
    }

    TEST_ISCHAR(bxi_iscntrl , iscntrl );
    TEST_ISCHAR(bxi_isprint , isprint );
    TEST_ISCHAR(bxi_isspace , isspace );
    TEST_ISCHAR(bxi_isgraph , isgraph );
    TEST_ISCHAR(bxi_ispunct , ispunct );
    TEST_ISCHAR(bxi_isalnum , isalnum );
    TEST_ISCHAR(bxi_isalpha , isalpha );
    TEST_ISCHAR(bxi_isupper , isupper );
    TEST_ISCHAR(bxi_islower , islower );
    TEST_ISCHAR(bxi_isdigit , isdigit );
    TEST_ISCHAR(bxi_isxdigit, isxdigit);
    /* isblank requires c99, no tests here  */
    /* TEST_ISCHAR(bxi_isblank , isblank ); */

    TEST_ISCHAR(bxi_2upper, (u32)toupper);
    TEST_ISCHAR(bxi_2lower, (u32)tolower);

#   undef TEST_ISCHAR
}

static void test_strings_bxi_str2lower(void)
{
    char buffer[] = "QUICK BROWN FOX JUMPS OVER THE LAZY DOG!";

    printf("        checking: bxi_str2lower\n");
    bxi_str2lower(buffer);
    if (bxi_strcmp(buffer, "quick brown fox jumps over the lazy dog!"))
        test_failed();
}

static void test_strings_bxi_str2upper(void)
{
    char buffer[] = "quick brown fox jumps over the lazy dog!";

    printf("        checking: bxi_str2upper\n");
    bxi_str2upper(buffer);
    if (bxi_strcmp(buffer, "QUICK BROWN FOX JUMPS OVER THE LAZY DOG!"))
        test_failed();
}

static void * my_malloc(u32 size, const char * file, u32 line)
{
    UNUSED(file);
    UNUSED(line);
    return calloc(size, 1);
}

static void my_free(void * ptr, const char * file, u32 line)
{
    UNUSED(file);
    UNUSED(line);
    free(ptr);
}

static void test_strings_bxi_strdup(void)
{
    bxi_malloc_set(my_malloc);
    bxi_free_set(my_free);

    printf("        checking: bxi_strdup\n");
    {
        char * str = bxi_strdup("Quick brown dog jumps over the lazy frog\n");
        if (bxi_strcmp(str, "Quick brown dog jumps over the lazy frog\n"))
            test_failed();

        bxi_free(str);
    }
}

static void test_strings_functions(void)
{
    printf("    functions:\n");

    test_strings_bxi_strhash();
    test_strings_bxi_strshiftl();
    test_strings_bxi_strtriml();
    test_strings_bxi_strtrimr();
    test_strings_bxi_strtrim();
    test_strings_bxi_strlen();
    test_strings_bxi_strcmp();
    test_strings_bxi_strprs();
    test_strings_bxi_strchr();
    test_strings_bxi_strcpy();
    test_strings_bxi_strstr();
    test_strings_bxi_is();
    test_strings_bxi_str2lower();
    test_strings_bxi_str2upper();
    test_strings_bxi_strdup();
}

void test_strings_bxistring(void)
{
    print_info;

    test_strings_functions();

    print_passed();
}
