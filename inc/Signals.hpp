#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <signal.h>
#include <sys/ioctl.h>
#include <csignal>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void    signalHandler(int signum);
void    setSignalHandler(void);

#endif