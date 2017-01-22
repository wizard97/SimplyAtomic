// Source:
// http://www.nongnu.org/avr-libc/user-manual/atomic_8h_source.html

/******************** HELPERS ***********************/
static __inline__ uint8_t __iSeiRetVal(void)
{
    __asm__ __volatile__ ("cpsie i" ::);
    return 1;
}

static __inline__ uint8_t __iCliRetVal(void)
{
    __asm__ __volatile__ ("cpsid i" ::);
    return 1;
}

static __inline__ void __iRestore(const  uint32_t *__s)
{
    uint32_t res = *__s;
    __asm__ __volatile__ ("MSR primask, %0" : : "r" (res) );
}

#define ATOMIC_RESTORESTATE uint8_t _sa_saved                           \
    __attribute__((__cleanup__(__iRestore))) = SREG

/******************** MACRO ***********************/

#define ATOMIC()
for (ATOMIC_RESTORESTATE, uint8_t _sa_done =  __iCliRetVal();           \
    _sa_done; _sa_done = 0 )
