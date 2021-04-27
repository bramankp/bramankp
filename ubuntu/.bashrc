# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# colored GCC warnings and errors
export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

#
# my prompts (may set Xterm title to user@host)
#
case "$TERM"
in
    putty*|xterm*)
        PS1='\[\033]0;\u@\h\007\]'
        ;;
    *)
        PS1=''
        ;;
esac
PS1+='[\u@\h:\W] '
PS2='[...] '

#
# my additional paths
#
newpaths=()
newpaths+=(~/.local/bin)
newpaths+=(~gtam/bin)
newpaths+=(~nano/bin)
envpath=${PATH}
for newpath in ${newpaths[@]}
do
    # remove possible duplicate
    envpath=${envpath//${newpath}}
    # clean up colons in variable
    envpath=${envpath/#:/}
    envpath=${envpath//::/:}
    envpath=${envpath/%:/}
    # append new path (if it exists)
    if [ -d ${newpath} ]
    then
        envpath+=":${newpath}"
    fi
done
export PATH=${envpath}
