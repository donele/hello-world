alias s="source ~/.zshrc"
export EDITOR=vim

alias lt='ls -lrt'
alias ll='ls -al'
alias tf='tail -f'
alias gt='git status'
alias ga='git add'
alias gc='git commit -v'
alias gd='git diff'
alias gl='git log --oneline'
alias gb='git branch'
alias cmake_debug='cmake -DCMAKE_BUILD_TYPE=Debug'

if [ -e $HOME/functions.sh ]
then
    source $HOME/functions.sh
fi

# tail -f of the most recent file in the directory.
function ltf {
last_file=`ls -rt *.log | tail -n 1`
echo $ tail -f $last_file
tail -f $last_file
}


# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/opt/anaconda3/bin/conda' 'shell.zsh' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/opt/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/opt/anaconda3/etc/profile.d/conda.sh"
    else
        export PATH="/opt/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
# <<< conda initialize <<<

