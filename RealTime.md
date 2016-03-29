# What is real-time, and why? #

In the context of robotics control, "[real-time](http://en.wikipedia.org/wiki/Real-time_computing)" refers to accurate timekeeping of system loops. That is, the system's response to an event must adhere to strict temporal deadlines, which, if not met, may lead to system failure.

Real-time systems are further classified by the consequences of a missed deadline: hard and soft. A hard real-time (HRT) system is used if a single missed deadline will invariably result in total system failure or cause great damage to the system or its physical surroundings. ATRIAS requires this HRT system because it is a fast-moving robot with powerful motors that can cause considerable damage to itself and its operators if not properly controlled.


# How do we achieve real-time? #

We achieve adequate real-time performance with [Xenomai](http://xenomai.org/).

The vanilla Linux kernel is not normally real-time capable. There exist several different kernel patches that allow the kernel to achieve varying degrees of real-time performance. In order of "hardest" to "softest" real-time performance, the three main projects are: [Xenomai](http://xenomai.org/), [RTAI](https://www.rtai.org/), and [CONFIG\_PREEMPT\_RT](https://rt.wiki.kernel.org/).

Brown and Martin conclude in [their paper](https://docs.google.com/viewer?url=https%3A%2F%2Fwww.osadl.org%2Ffileadmin%2Fdam%2Frtlws%2F12%2FBrown.pdf) that a process run in Xenomai user space outperforms those run in stock and PREEMPT\_RT kernels in both kernel space and user space by a factor of 5 or more in 100% hard real-time performance (p. 13).

Although others have reported success with RT\_PREEMPT for similar projects, we have had difficulties obtaining HRT performance under RT\_PREEMPT. Therefore, we are utilizing Xenomai. One goal of ours, however, is to be able to run in HRT under RT\_PREEMPT for the increased hardware support.

ATRIAS runs on controllers that operate at 1 kHz. While this is fairly fast, it is not so fast that several microseconds of jitter (imperfect meeting of deadlines) poses any significant problems.

Paul McKenney [provides a good overview](http://lwn.net/Articles/146861/) of what the PREEMPT\_RT patch aims to do, and how.

# Notes #

## Real-time safety ##

  * Don't make system calls (e.g., writing to disk). There are some exceptions here -- for example, most functions that require linking with librt are safe (as documented [here](http://orocos.org/forum/orocos/orocos-users/how-does-orocos-do-real-time-os-access)).

[Orocos RTT RT\_PREEMPT](http://www.orocos.org/forum/rtt/rtt-dev/orocos-rtt-rt-preempt):
  * Page faults are bad. Locking memory will prevent paging.
  * Don't dynamically allocate memory in the real-time part of the application.
  * Don't use RTT::Logger (not real-time).


# Reading #

[Establishing timing requirements for control loops in real-time systems](https://docs.google.com/viewer?url=http://www.cs.st-andrews.ac.uk/~pn/establishing-timing-reqs-mm02.pdf&pli=1)

[Real-Time Performance Analysis in Linux-Based Robotic Systems](https://docs.google.com/viewer?url=http%3A%2F%2Fkernel.org%2Fdoc%2Fols%2F2009%2Fols2009-pages-331-339.pdf)

[RTLinux manifesto](https://docs.google.com/viewer?url=http%3A%2F%2Fwww.yodaiken.com%2Fpapers%2Frtlmanifesto.pdf)


---


## Needs organization: ##

Printing to console breaks real-time!

[Real-time for Linux kernel newbies](http://groups.google.com/group/linuxkernelnewbies/browse_thread/thread/69780b554fd7fd61/25e69a7cf81c04c9?pli=1)

[What is LXRT?](https://www.rtai.org/documentation/magma/html/api/whatis_lxrt.html)

[How is realtime accomplished in Orocos?](http://www.orocos.org/node/503)

[EtherLab has to be run in kernel space in order to have low jitter.](http://permalink.gmane.org/gmane.linux.real-time.rtai/24585)

[SOEM can be run with RT scheduler.. but is it HRT?](https://amigo.wtb.tue.nl/svn/amigo/code/tue-ros-pkg/trunk/tue_actuation/amigo_etherCAT/soem.ops)

[SOEM needs RTnet on top of Xenomai or RTAI to run in HRT.](http://www.orocos.org/forum/orocos/orocos-users/ethercat-driver-orocos)

[The transmission of a packet with a minimum packetsize of ~60 bytes is in the range of 5us.](http://lists.etherlab.org/pipermail/etherlab-users/2011/001247.html)

[The jitter of EtherCAT Master in user space was less than 50µs and the time used by the master was less than 3µs.](http://lists.etherlab.org/pipermail/etherlab-users/2009/000535.html)

[User space scheduling with RTAI fails for EtherCAT?](http://lists.etherlab.org/pipermail/etherlab-users/2011/001187.html)

[EtherLab user space library not designed to work with LXRT, etc.](http://lists.etherlab.org/pipermail/etherlab-users/2010/000804.html)

[Herman Bruyninchx's guide to real-time and embedded operating systems.](http://people.mech.kuleuven.be/~bruyninc/rthowto/rtHOWTO.pdf)

[A paper on installing a realtime Linux kernel](http://www.mate.tue.nl/mate/pdfs/10018.pdf)


---


The Orocos/LXRT node needs to be run as root (apparently; don't know why yet). Can run at 5000+ Hz, even while publishing ROS messages. Orocos/gnulinux node, even when run as root, cannot go beyond 950 Hz. I'd like to think this is real-time, because running 8 instances of `cat /dev/urandom > somefile` doesn't seem to affect the loop rate.

I've been testing ROS publishing frequency with 'rostopic hz' and noticed at times that CPU-heavy tasks would make it look as if the publish frequency was slowing down, but it is entirely possible that since rostopic is not a real-time process, rostopic simply fails to listen to the published topic and that publishing chugs along at 1 kHz regardless.