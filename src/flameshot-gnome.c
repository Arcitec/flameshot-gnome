// Copyright (C) 2024 Arcitec
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int contains_whitespace(const char *str) {
    return strpbrk(str, " \t\n\r\f\v") != NULL;
}

int main(int argc, char *argv[]) {
    // Create a child process.
    // NOTE: The subprocess forking is NECESSARY to get screenshot permissions
    // when running in a GNOME keybinding. Otherwise flameshot will be blocked!
    pid_t parent_pid = getpid();
    pid_t child_pid = fork();

    if (child_pid < 0) {
        // Failed to create a child process.
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // This is the child process.

        // Generate command-line arguments for the flameshot process.
        int flameshot_argc = argc >= 1 ? argc + 1 : 2; // +1 for trailing NULL.
        char *flameshot_argv[flameshot_argc];
        flameshot_argv[0] = "flameshot";
        for (int i = 1; i < argc; i++) {
            flameshot_argv[i] = argv[i];
        }
        flameshot_argv[flameshot_argc - 1] = NULL;

        // Automatically inject QT's Wayland flag if necessary.
        bool is_wayland = getenv("WAYLAND_DISPLAY") != NULL;
        if (is_wayland) {
            setenv("QT_QPA_PLATFORM", "wayland", 1);
        }

        // Display the active arguments.
        printf(
            "Running Flameshot%s with %d argument%s...\n",
            is_wayland ? " (Wayland)" : "",
            flameshot_argc - 2, // Minus program-name and NULL.
            flameshot_argc == 3 ? "" : "s" // "1 argument" or "X arguments".
        );
        printf("> %s ", flameshot_argv[0]);
        for (int i = 1, len = flameshot_argc - 1; i < len; i++) {
            // NOTE: Very basic escaping, since it's just for display purposes.
            printf(
                contains_whitespace(flameshot_argv[i]) ? "\"%s\" " : "%s ",
                flameshot_argv[i]
            );
        }
        printf("\n");

        // Run Flameshot.
        // NOTE: This completely replaces the entire child process.
        execvp(flameshot_argv[0], flameshot_argv);

        // If execution continued after "execvp", an error has occurred.
        perror("execvp");
        return 1;
    } else {
        // This is the parent process.

        // Wait for the child process to finish.
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            // Child process exited with a status code.
            int exit_status = WEXITSTATUS(status);
            return exit_status;
        } else {
            // Child process terminated unexpectedly.
            return -1;
        }
    }

    return 0;
}
