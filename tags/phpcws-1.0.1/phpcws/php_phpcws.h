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

/* C++ Include C by Zhang Yan (start) */
extern "C" {

/* $Id: phpcws.cpp,v 1.0 2008/12/29 16:42:09 zhangyan Exp $ */

#ifndef PHP_PHPCWS_H
#define PHP_PHPCWS_H

extern zend_module_entry phpcws_module_entry;
#define phpext_phpcws_ptr &phpcws_module_entry

#ifdef PHP_WIN32
#define PHP_PHPCWS_API __declspec(dllexport)
#else
#define PHP_PHPCWS_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(phpcws);
PHP_MSHUTDOWN_FUNCTION(phpcws);
PHP_RINIT_FUNCTION(phpcws);
PHP_RSHUTDOWN_FUNCTION(phpcws);
PHP_MINFO_FUNCTION(phpcws);

PHP_FUNCTION(confirm_phpcws_compiled);	/* For testing, remove later. */
PHP_FUNCTION(phpcws_split);

#define PHP_PHPCWS_VERSION "1.0.0 2009-02-13"

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(phpcws)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(phpcws)
*/
ZEND_BEGIN_MODULE_GLOBALS(phpcws)
        zend_bool  is_load_dict;
        TCADB *userdict_adb;
        char *dict_path;
ZEND_END_MODULE_GLOBALS(phpcws)

/* In every utility function you add that needs to use variables 
   in php_phpcws_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PHPCWS_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PHPCWS_G(v) TSRMG(phpcws_globals_id, zend_phpcws_globals *, v)
#else
#define PHPCWS_G(v) (phpcws_globals.v)
#endif

#endif	/* PHP_PHPCWS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

/* C++ Include C by Zhang Yan (stop) */
}
