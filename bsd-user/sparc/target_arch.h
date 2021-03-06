
#ifndef _TARGET_ARCH_H_
#define _TARGET_ARCH_H_

void bsd_sparc_save_window(CPUSPARCState *env);
void bsd_sparc_restore_window(CPUSPARCState *env);
void bsd_sparc_flush_windows(CPUSPARCState *env);

#define target_cpu_set_tls(env, newtls)

#endif /* ! _TARGET_ARCH_H_ */
