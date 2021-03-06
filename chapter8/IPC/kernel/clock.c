#include "type.h"
#include "const.h"
#include "tty.h"
#include "console.h"
#include "protect.h"
#include "proc.h"
#include "proto.h"
#include "global.h"

PUBLIC void clock_handler(int irq)
{
	ticks++;
	p_proc_ready->ticks --;

	if (k_reenter != 0) {
		return ;
	}

	if (p_proc_ready->ticks > 0) {
		return ;
	}

	schedule();
}

PUBLIC void milli_delay(int milli_sec)
{
	int t = get_ticks(__FILE__, __LINE__);
	/*disp_str("HALIDEFENGEXIAN-----");*/
	/*disp_int(t);*/
	/*disp_str("-------HALIDEFENGEXIAN\n");*/
	
	while (((get_ticks(__FILE__, __LINE__) - t) * 1000 / HZ) < milli_sec) {}
	/*disp_str("NEVER HAVE A DREAM COME TRUE!!!\n");*/
}

PUBLIC void init_clock()
{
	out_byte(TIMER_MODE, RATE_GENERATOR);
	out_byte(TIMER0, (TIMER_FREQ / HZ));
	out_byte(TIMER0, ((TIMER_FREQ / HZ) >> 8));

	put_irq_handler(CLOCK_IRQ, clock_handler);
	enable_irq(CLOCK_IRQ);
}
