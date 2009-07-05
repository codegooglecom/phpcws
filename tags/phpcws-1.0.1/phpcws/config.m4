dnl $Id$
dnl config.m4 for extension phpcws

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(phpcws, for phpcws support,
dnl Make sure that the comment is aligned:
dnl [  --with-phpcws             Include phpcws support])

PHP_ARG_WITH(tc, for Tokyo Cabinet DBM support for userdict.tch,
[  --with-tc[=PATH]          PATH is the Tokyo Cabinet DBM base directory])

dnl Otherwise use enable:

PHP_ARG_ENABLE(phpcws, whether to enable phpcws support,
dnl Make sure that the comment is aligned:
[  --enable-phpcws           Enable phpcws support])

LDFLAGS="$LDFLAGS -L${PHP_TC}/lib/static -L./ICTCLAS -ltokyocabinet -lz -lbz2 -lpthread -lm -lc -lICTCLAS30"
CPPFLAGS="$CPPFLAGS -I${PHP_TC}/include -Wall -Wunused -O3 -DOS_LINUX"

PHP_REQUIRE_CXX()/
PHP_ADD_LIBRARY(stdc++, "", LDFLAGS)

if test "$PHP_PHPCWS" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-phpcws -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/phpcws.h"  # you most likely want to change this
  dnl if test -r $PHP_PHPCWS/$SEARCH_FOR; then # path given as parameter
  dnl   PHPCWS_DIR=$PHP_PHPCWS
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for phpcws files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PHPCWS_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PHPCWS_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the phpcws distribution])
  dnl fi

  dnl # --with-phpcws -> add include path
  dnl PHP_ADD_INCLUDE($PHPCWS_DIR/include)

  dnl # --with-phpcws -> check for lib and symbol presence
  dnl LIBNAME=phpcws # you may want to change this
  dnl LIBSYMBOL=phpcws # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PHPCWS_DIR/lib, PHPCWS_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PHPCWSLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong phpcws lib version or lib not found])
  dnl ],[
  dnl   -L$PHPCWS_DIR/lib -lm -ldl
  dnl ])
  dnl
  dnl PHP_SUBST(PHPCWS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(phpcws, phpcws.cpp, $ext_shared)
fi
