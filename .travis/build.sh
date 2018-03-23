#! /bin/sh

make distclean &>/dev/null || true
phpize || exit 1
./configure || exit 1
make clean all &&
make install || exit 1

