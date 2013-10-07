/*
 *  FreeBSD siginfo related definitions
 *
 *  Copyright (c) 2013 Stacey D. Son
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _TARGET_OS_SIGINFO_H_
#define _TARGET_OS_SIGINFO_H_

#define TARGET_NSIG         128
#define TARGET_NSIG_BPW     (sizeof(uint32_t) * 8)
#define TARGET_NSIG_WORDS   (TARGET_NSIG / TARGET_NSIG_BPW)

/* this struct defines a stack used during syscall handling */
typedef struct target_sigaltstack {
    abi_long    ss_sp;
    abi_ulong   ss_size;
    abi_long    ss_flags;
} target_stack_t;

typedef struct {
    uint32_t __bits[TARGET_NSIG_WORDS];
} target_sigset_t;

struct target_sigaction {
    abi_ulong   _sa_handler;
    int32_t     sa_flags;
    target_sigset_t sa_mask;
};

union target_sigval {
    int32_t sival_int;
    abi_ulong sival_ptr;
    int32_t sigval_int;
    abi_ulong sigval_ptr;
};

typedef struct target_siginfo {
    int32_t si_signo;   /* signal number */
    int32_t si_errno;   /* errno association */
    int32_t si_code;    /* signal code */
    int32_t si_pid;     /* sending process */
    int32_t si_uid;     /* sender's ruid */
    int32_t si_status;  /* exit value */
    abi_ulong si_addr;  /* faulting instruction */
    union target_sigval si_value;   /* signal value */
    union {
        struct {
            int32_t _trapno;    /* machine specific trap code */
        } _fault;

        /* POSIX.1b timers */
        struct {
            int32_t _timerid;
            int32_t _overrun;
        } _timer;

        struct {
            int32_t _mqd;
        } _mesgp;

        /* SIGPOLL */
        struct {
            int _band;  /* POLL_IN, POLL_OUT, POLL_MSG */
        } _poll;

        struct {
            abi_long __spare1__;
            int32_t  __spare2_[7];
        } __spare__;
    } _reason;
} target_siginfo_t;

#define target_si_signo     si_signo
#define target_si_code      si_code
#define target_si_errno     si_errno
#define target_si_addr      si_addr

/* SIGILL si_codes */
#define TARGET_ILL_ILLOPC   (1) /* Illegal opcode. */
#define TARGET_ILL_ILLOPN   (2) /* Illegal operand. */
#define TARGET_ILL_ILLADR   (3) /* Illegal addressing mode. */
#define TARGET_ILL_ILLTRP   (4) /* Illegal trap. */
#define TARGET_ILL_PRVOPC   (5) /* Privileged opcode. */
#define TARGET_ILL_PRVREG   (6) /* Privileged register. */
#define TARGET_ILL_COPROC   (7) /* Coprocessor error. */
#define TARGET_ILL_BADSTK   (8) /* Internal stack error. */

/* SIGSEGV si_codes */
#define TARGET_SEGV_MAPERR  (1) /* address not mapped to object */
#define TARGET_SEGV_ACCERR  (2) /* invalid permissions for mapped
                                           object */

/* SIGTRAP si_codes */
#define TARGET_TRAP_BRKPT   (1) /* process beakpoint */
#define TARGET_TRAP_TRACE   (2) /* process trace trap */

#endif /* !_TARGET_OS_SIGINFO_H_ */
