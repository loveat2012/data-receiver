#!/bin/bash

set -x
aclocal 
autoheader
automake --foreign --copy
autoconf
