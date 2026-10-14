$NetBSD$

Fix conflicts with C11 thread definitions in newer glibc.

Based on a patch by Viorel Munteanu (Gentoo):
https://github.com/gentoo/gentoo/commit/3b736f182cfc78719c05eba9059ec8fe51d92643

--- include/c11/threads_posix.h
+++ include/c11/threads_posix.h
@@ -51,8 +51,10 @@
 #include <pthread.h>
 
 /*---------------------------- macros ----------------------------*/
-#define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
-#ifdef INIT_ONCE_STATIC_INIT
+#ifndef __once_flag_defined
+#  define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
+#endif
+#ifdef PTHREAD_DESTRUCTOR_ITERATIONS
 #define TSS_DTOR_ITERATIONS PTHREAD_DESTRUCTOR_ITERATIONS
 #else
 #define TSS_DTOR_ITERATIONS 1  // assume TSS dtor MAY be called at least once.
@@ -66,7 +68,9 @@
 typedef pthread_t       thrd_t;
 typedef pthread_key_t   tss_t;
 typedef pthread_mutex_t mtx_t;
+#ifndef __once_flag_defined
 typedef pthread_once_t  once_flag;
+#endif
 
 
 /*
@@ -90,11 +94,13 @@
 
 /*--------------- 7.25.2 Initialization functions ---------------*/
 // 7.25.2.1
+#ifndef __once_flag_defined
 static inline void
 call_once(once_flag *flag, void (*func)(void))
 {
     pthread_once(flag, func);
 }
+#endif
 
 
 /*------------- 7.25.3 Condition variable functions -------------*/
