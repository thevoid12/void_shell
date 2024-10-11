// psinfo command  lists currently running processes with details such as
//  PID (Process ID), PPID (Parent Process ID), State, and Command

#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>
#include <unistd.h>
#include <sys/types.h>

// Function to implement psinfo command
void execute_psinfo() {
    pid_t pids[4096];  // Array to store PIDs
    int num_pids = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));

    if (num_pids <= 0) {
        perror("proc_listpids");
        return;
    }

    int total_pids = num_pids / sizeof(pid_t);

    printf("%-10s %-10s %-10s %s\n", "PID", "PPID", "STATE", "CMD");

    for (int i = 0; i < total_pids; i++) {
        pid_t pid = pids[i];
        if (pid == 0) continue;  // Skip invalid PIDs

        struct proc_bsdinfo proc_info;
        int ret = proc_pidinfo(pid, PROC_PIDTBSDINFO, 0, &proc_info, sizeof(proc_info));

        if (ret != sizeof(proc_info)) {
            continue;  // Unable to retrieve info for this PID
        }

        // Display PID, PPID, State, and Command
        printf("%-10d %-10d %-10c %s\n",
               proc_info.pbi_pid,
               proc_info.pbi_ppid,
               proc_info.pbi_status,
               proc_info.pbi_comm);
    }
}
