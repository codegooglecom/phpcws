/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Zhang Yan, China (http://blog.s135.com)(E-mail: net@s135.com)|
  +----------------------------------------------------------------------+
*/

/* $Id: phpcws.c,v 1.0 2008/12/29 16:42:09 zhangyan Exp $ */

/* C++ Include C by Zhang Yan (start) */
extern "C" {

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include <tcutil.h> 
#include <tcadb.h> 

/* C++ Include C by Zhang Yan (stop) */
}
#include "ICTCLAS/ICTCLAS30.h"
#include "php_phpcws.h"

/* If you declare any globals in php_phpcws.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(phpcws)

/* True global resources - no need for thread safety here */
static int le_phpcws;

/* {{{ phpcws_functions[]
 *
 * Every user visible function must have an entry in phpcws_functions[].
 */
zend_function_entry phpcws_functions[] = {
	PHP_FE(confirm_phpcws_compiled,	NULL)		/* For testing, remove later. */
        PHP_FE(phpcws_split, NULL)
	{NULL, NULL, NULL}	/* Must be the last line in phpcws_functions[] */
};
/* }}} */

/* {{{ phpcws_module_entry
 */
zend_module_entry phpcws_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"phpcws",
	phpcws_functions,
	PHP_MINIT(phpcws),
	PHP_MSHUTDOWN(phpcws),
	PHP_RINIT(phpcws),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(phpcws),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(phpcws),
#if ZEND_MODULE_API_NO >= 20010901
        PHP_PHPCWS_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PHPCWS
BEGIN_EXTERN_C()
ZEND_GET_MODULE(phpcws)
END_EXTERN_C()
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phpcws.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_phpcws_globals, phpcws_globals)
    STD_PHP_INI_ENTRY("phpcws.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_phpcws_globals, phpcws_globals)
PHP_INI_END()
*/
/* }}} */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("phpcws.dict_path", "/usr/local/phpcws", PHP_INI_ALL, OnUpdateString, dict_path, zend_phpcws_globals, phpcws_globals)
PHP_INI_END()

/* {{{ php_phpcws_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_phpcws_init_globals(zend_phpcws_globals *phpcws_globals)
{
	phpcws_globals->global_value = 0;
	phpcws_globals->global_string = NULL;
}
*/
/* }}} */

static void php_phpcws_init_globals(zend_phpcws_globals *phpcws_globals)
{
}

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(phpcws)
{
        ZEND_INIT_MODULE_GLOBALS(phpcws, php_phpcws_init_globals, NULL);
	REGISTER_INI_ENTRIES();
        PHPCWS_G(is_load_dict) = 0;
        PHPCWS_G(userdict_adb) = tcadbnew();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(phpcws)
{
	UNREGISTER_INI_ENTRIES();
        tcadbclose(PHPCWS_G(userdict_adb));
        tcadbdel(PHPCWS_G(userdict_adb));
        ICTCLAS_Exit();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(phpcws)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(phpcws)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(phpcws)
{
	php_info_print_table_start();
        php_info_print_table_header(2, "PHP Chinese Word Segmentation", "enabled");
        php_info_print_table_row(2, "Version", PHP_PHPCWS_VERSION);
        php_info_print_table_row(2, "Author", "Zhang Yan (http://blog.s135.com)");
        php_info_print_table_row(2, "Official website", "http://code.google.com/p/phpcws");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_phpcws_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_phpcws_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "phpcws", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

PHP_FUNCTION(phpcws_split)
{
    int MERGE_NUM = 5; //Reverse Maximum Matching words
    char *string = NULL;
    char *interpunction = "";
    char *dictpath = NULL;
    char *userdict = NULL;
    int string_len = 0, interpunction_len = 0, res, len, words_num = 0, token_maxlen = 0, token_len = 0;
    char *strg = NULL;
    char *strg_sec = NULL;
    const char *pResult = NULL;
    char *seps = " ";
    char *token = NULL;
    char *token_sec = NULL;
    char *userdict_value;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|s", &string, &string_len, &interpunction, &interpunction_len) == FAILURE) {
        return;
    }

    if (interpunction_len > 0 && strcasecmp(interpunction, "default") == 0) {
        interpunction_len = spprintf(&interpunction, 0, "%s", ",.!£¡£¢£££¤£¥£¦£à£§£¨£©¡²¡³¡´¡µ¡¶¡·¡¸¡¹¡º¡»¡¼¡½¡¾¡¿£®£ª£«£¬£­£®¡£¡¢£¿¡­¡ª¡¤¡¥¡¦¡§¡®¡¯¡°¡±¡©¡«¡¬¡Ã£¢£¯£º£»£ü¡¨£¼£½£¾£¿£À£Û£Ü£Ý£Þ£ß£à£û£ü£ý£þ");
    }

    if (PHPCWS_G(is_load_dict) == 0)
    {
        res = spprintf(&dictpath, 0, "%s", INI_STR("phpcws.dict_path"));
        if(!ICTCLAS_Init(dictpath))
        {
            return;
        }

        /* init user dict */
        res = spprintf(&userdict, 0, "%s/%s", dictpath, "userdict.tch#mode=rf#opts=1d#bnum=1000000");

        if(!tcadbopen(PHPCWS_G(userdict_adb), userdict))
        {
            return;
        }

        PHPCWS_G(is_load_dict) = 1;
    }

    pResult = ICTCLAS_ParagraphProcess(string, 0);
    len = spprintf(&strg, 0, "%s", pResult);
    len = len - 1;
    strncpy(strg,strg,len);
    res = spprintf(&strg_sec, 0, "%s", strg);

    token = strtok(strg, seps);
    while( token != NULL )
    {
        token_len = strlen(token);
        if (token_len > token_maxlen)
        {
            token_maxlen = token_len;
        }
        words_num++;
        token = strtok( NULL, seps);
    }

    char cws_words[words_num][token_maxlen+1];
    memset(cws_words, '\0', sizeof(cws_words));
    words_num = 0;
    token_sec = strtok(strg_sec, seps); 
    while( token_sec != NULL )
    {
        sprintf(cws_words[words_num], "%s", token_sec);
        words_num++;
        token_sec = strtok( NULL, seps);
    }

    /* Reverse Maximum Matching Algorithm  */
    int u_max = words_num, u_min = 0, u_tmp, u_str;
    char *ustr_tmp = (char *)emalloc(100);
    char *ustr_tmp1 = (char *)emalloc(100);
    char *strg_output = (char *)emalloc(len * 2);
    char *strg_tmp = (char *)emalloc(len * 2);
    res = spprintf(&ustr_tmp, 0, "%s", "");
    res = spprintf(&ustr_tmp1, 0, "%s", "");
    res = spprintf(&strg_output, 0, "%s", "");
    res = spprintf(&strg_tmp, 0, "%s", "");
    while (u_min >=0 && u_max > 0)
    {
        u_tmp = u_max;
        u_max = u_tmp - 1;
        u_min = u_tmp - MERGE_NUM;
        if(u_min < 0)
        {
            u_min = 0;
        }

        for (u_tmp = u_min; u_tmp <= u_max; u_tmp++)
        {
            for(u_str = u_tmp; u_str <= u_max; u_str++)
            {
                res = spprintf(&ustr_tmp1, 0, "%s%s", ustr_tmp, cws_words[u_str]);
                efree(ustr_tmp);
                res = spprintf(&ustr_tmp, 0, "%s", ustr_tmp1);
                efree(ustr_tmp1);
            }
            userdict_value = tcadbget2(PHPCWS_G(userdict_adb), ustr_tmp);
            if(u_tmp == u_max || userdict_value != NULL)
            {
                if (strstr(interpunction, ustr_tmp) == 0 || interpunction_len == 0)
                {
                    res = spprintf(&strg_tmp, 0, "%s %s", ustr_tmp, strg_output);
                    efree(strg_output);
                    len = spprintf(&strg_output, 0, "%s", strg_tmp);
                    efree(strg_tmp);
                }
                free(userdict_value);
                u_max = u_tmp;
                efree(ustr_tmp);
                res = spprintf(&ustr_tmp, 0, "%s", "");
                break;
            } else {
                free(userdict_value);
                efree(ustr_tmp);
                res = spprintf(&ustr_tmp, 0, "%s", "");
            }
        }
    }

    RETURN_STRINGL(strg_output, len, 0);
}
