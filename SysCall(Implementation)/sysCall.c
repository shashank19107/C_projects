#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>

// Used this macro to be able to pass variables to the syscall
// It takes one integer, PID.
SYSCALL_DEFINE1(sys_petime, int, pid)
{
  // Using task_struct struct from sched.h, which has task's (process)
  // various data mostly about scheduling.
  struct task_struct *task;
  u64 start_time, elapsed;

  // Get process with PID.
  task = pid_task(find_vpid(pid), PIDTYPE_PID);
  // If process is not found.
  if (task == NULL)
  {
    // Print the error to the kernel buffer
    printk(KERN_INFO "Cannot find a process with that PID: %d\n", pid);
  }
  else
  {
    // Taken from "taskstats.c" source code (line 240-241).
    // Used the logic behind calculating the delta time in that source.
    // Get current nanoseconds since boot
    start_time = ktime_get_ns();
    // Difference
    elapsed = start_time - task->real_start_time;
    // Print result to the kernel buffer
	printk("PID: %d",pid);
	printk("rt_priority: %llu ", task->rt_priority);
	printk("it_real_value: %llu ", task->it_real_value);
	printk("it_prof_value: %llu ", task->it_prof_value);
	printk("it_virt_value: %llu ", task->it_virt_value);
	//printk();
    printk(KERN_INFO "PID: %d has ELAPSED %llu nanoseconds.", pid, elapsed);
  }

  // If nothing goes wrong, return 0 as successful
  return 0;
}
*/
unsigned long rt_priority;
	unsigned long it_real_value, it_prof_value, it_virt_value;
	unsigned long it_real_incr, it_prof_incr, it_virt_incr;

*/
