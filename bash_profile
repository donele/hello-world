#!/bin/bash

if [ -f ~/.bashrc ]; then
	source ~/.bashrc
fi

# Setting PATH for Python 3.6
# The original version is saved in .bash_profile.pysave
PATH="/Library/Frameworks/Python.framework/Versions/3.6/bin:${PATH}"
export PATH

# added by Miniconda3 4.3.21 installer
export PATH="/Users/jdlee/miniconda3/bin:$PATH"
