#ifndef SIGNALS_HPP
#define SIGNALS_HPP

#include <cstdio>
#include <csignal>
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <readline/history.h>
#include <readline/readline.h>

void    setSignalHandler(void);
void    signalHandler(int signum);

#endif