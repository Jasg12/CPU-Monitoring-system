#ifndef MONITORING_SYSTEM_H
#define MONITORING_SYSTEM_H

#include<iostream>
#include<fstream>
#include<stdint.h>
#include<time.h>

using namespace std;

#define NO_OF_SERVERS 1000 /*Number of servers*/
#define TOTAL_NO_OF_MINUTES 1440 /* Number of minutes in a day 24*60 */

/*Server Structure */
typedef struct monitoring_system
{
	int unix_timestamp;		//unix timestamp;
	uint32_t ip[4];			//Ip address
	uint32_t cpu_1;			//CPU 1 with id 0
	uint32_t cpu_2;			//CPU 2 with id 1
	uint32_t cpu_usage_1;	//% of CPU usage of CPU 1
	uint32_t cpu_usage_2;	//% of CPU usage of CPU 2
}monitoring_system;

#endif
