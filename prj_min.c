// Event queue prj_evt_que
typedef u8 evt_t;

#ifndef CFG_PARAM_SIZE
	#define CFG_PARAM_SIZE 0U  // 为什么不是 (0U) ?
#endif

#if (CFG_PARAM_SIZE == 0U)	
#elif (CFG_PARAM_SIZE == 1U)
	typedef u8 param_t;
#elif (CFG_PARAM_SIZE == 2U)	
	typedef u16 param_t;
#elif (CFG_PARAM_SIZE == 4U)	
	typedef u32 param_t;
#elif (CFG_PARAM_SIZE == 8U)	
	typedef u64 param_t;
#else
	#error "CFG_PARAM_SIZE defined incorrectly, expected 0U, 1U, 2U, 4U or 8U"
#endif	

typedef struct
{
	evt_t ev;
#if (CFG_PARAM_SIZE != 0U)
	param_t par;
#endif	
}prj_evt_t;

static prj_evt_t prj_evt_que[10];


// active object control block
#ifndef CFG_TIMER_SIZE
	#define CFG_TIMER_SIZE 0U  // 为什么不是 (0U) ?
#endif

#if (CFG_TIMER_SIZE == 0U)	
#elif (CFG_TIMER_SIZE == 1U)
	typedef u8 timer_t;
#elif (CFG_TIMER_SIZE == 2U)	
	typedef u16 timer_t;
#elif (CFG_TIMER_SIZE == 4U)	
	typedef u32 timer_t;
#else
	#error "CFG_TIMER_SIZE defined incorrectly, expected 0U, 1U, 2U, 4U"
#endif	

typedef struct prj_ao_t
{
	prj_hsm_t super;
	
	// priority
	u8 volatile prio;
	
	// queue ops
	u8 volatile head;
	u8 volatile tail;	
	u8 volatile used;

	// timer
#if (CFG_TIMER_SIZE != 0U)
	timer_t timer;
#endif	
}prj_ao_t;

typedef struct prj_xx_ao
{
	prj_ao_t super;
	//xx
}prj_xx_ao;

prj_xx_ao xx_ao;

typedef struct 
{
	prj_ao_t *ao;
	prj_evt_t *eq;
	u8 qlen;
}prj_acb_t;

prj_acb_t const ROM prj_acb[] = 
{
	{(prj_ao_t*)0, (prj_evt_t*)0, 0U},
	{(prj_ao_t*)&xx_ao, (prj_evt_t*)prj_evt_que, DIM(prj_evt_que)},  // #define DIM(array_) (sizeof(array_) / sizeof((array_)[0]))
};