*This project has been created as part of the 42 curriculum by coholbur.*

# Philosophers

Is a project that makes possible a dining scenario built with strict rules and which imposes particular synchronization regarding the timing of eating, thinking, and sleeping. The key to solving this project lies in properly managing forks, implementing threads correctly, and protecting shared resources using mutexes.

## We love the rules

- One or more philosophers sit at a round table around a bowl of spaghetti 
- While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are as many forks as philosophers.
- To eat, a philosopher must pick up both the fork to their left and the fork to their right.
- After eating, they put the forks back, sleep, then think again..
- The simulation stops if a philosopher dies of starvation.
- Philosophers must eat and should never starve.
- They do not communicate and cannot know if another philosopher is about to die.
- Avoiding death is essential for philosophers. Did they make it?
 
## Instructions

The program takes 5 arguments :

```bash
	number_of_philosophers #nbr
	time_to_die(in ms) #die
	time_to_eat(in ms) #eat
	time_to_sleep(in ms) #sleep 
	number_of_times_each_philosopher_must_eat(optional argument) #nbr_meals
```
A Makefile must be created and the program should to be compiled at the root of the repository, using :

```bash
	make
```
	The project must be executed as follows:

```bash
	./philo <nbr> <die> <eat> <sleep> <nbr_meals>
```


### Setup

The flow of the process is clearly visible in `main.c`, with each step called by predictably named functions.

#### Threads

 * Creating Philosopher Threads:
`ft_protected_create` handles thread creation for all philosophers. If thread creation fails, an error is printed and resources are cleaned up.

 * Monitor Thread:
`ft_protected_monitor_thread` launches a separate monitor thread (`ft_simultan_monitor`) that watches the simulation for philosopher deaths. The main program waits (`pthread_join`) for the monitor to finish before proceeding.

 * Joining Threads:
`ft_protected_join_threads` joins all philosopher threads to ensure they complete before cleaning up resources. If joining fails, cleanup is still performed to avoid memory leaks.

Each function ensures proper error handling and resource management, keeping the simulation safe and synchronized.

#### Mutexes

Mutexes are carefully implemented in the right places, following a logical structure to protect shared resources and ensure safe thread synchronization throughout the simulation.

To analyze mutexes and threads, use the following command:

```bash
valgrind --tool=helgrind ./philo nbr die eat sleep [nbr_meals]
```
#### Memory allocation

The functions responsible for memory allocation, `ft_mem_forks` and `ft_mem_philo`, can be found in `ft_memory_allocation.c`.

- `ft_mem_forks` allocates memory for all forks and initializes their mutexes. 

- `ft_mem_philo` allocates memory for each philosopher and initializes their last_meal_mutex. 

The program handles memory allocation very robustly. All resources are protected, and error handling is implemented throughout, making it extremely difficult for the program to crash due to allocation or mutex issues.

## Resources

 - **Peer-to-peer learning** – was the most valuable resource; this project was developed with guidance and collaboration from other 42 students;
 - **Books** – Classic references to learn C from scratch and understand various programming notions;
 - **Tutorials and articles** – Consulted to gain a better understanding of thread and mutex usage.

### AI Assistance
AI tools were used to help:
- Create diagrams and schemas to visualize how functions work and how data flows
- Help with README

No AI was used to write the functions directly; all code logic and implementation are my own work and personal vision.
