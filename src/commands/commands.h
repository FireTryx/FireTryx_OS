#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
    const char *name;
    void (*func)();
} Command;

// COMMANDS
void handle_command(const char *command);

extern int num_commands;

#endif