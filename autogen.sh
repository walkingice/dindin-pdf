#!/bin/sh

rm -rf autom4te.cache
rm -f aclocal.m4 ltmain.sh

touch README
touch ABOUT-NLS

echo "Running autopoint..." ; autopoint -f || :
echo "Running aclocal..." ; aclocal -I m4 $ACLOCAL_FLAGS || exit 1
echo "Running autoconf..." ; autoconf || exit 1
echo "Running autoheader..." ; autoheader || exit 1
echo "Running intltoolize..." ; (intltoolize -c --automake --force) || exit 1
echo "Running automake..." ; automake --add-missing --copy --gnu || exit 1

if [ -z "$NOCONFIGURE" ]; then
	./configure "$@"
fi
