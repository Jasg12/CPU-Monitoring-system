/************************* CPU Monitoring System****************************/
			

#include"monitoring_system.h"

/*	Main Function
	ARGV[1] contains output directory path and output file name */

int main(int argc, char *argv[])
{
	time_t raw_time;
	struct tm *timeinfo;

	/*Need to collect the logs for the day 2014-10-31 */
	int year = 2014, month = 10, day = 31, h = 0, min = 0, sec = 0;
	
	/* Allocate memory for 1000 servers */
	monitoring_system *server = new monitoring_system[NO_OF_SERVERS];
	ofstream file;

	if (argc != 2)
	{
		cout << "Please enter output directory ";
		return 0;
	}

	if (server == NULL)
	{
		cout << "Allocation of memory failed";
		return 0;
	}

	/*Output directory created*/
	file.open(argv[1]);

	cout << "Logs being generated" << endl;

	/* Get current time Unixtimestamp */
	time(&raw_time);

	/* Get current time in YYYY-mm-DD HH:MM:SS format */
	timeinfo = localtime(&raw_time);

	/*Convert the time to 2014-10-31 */
	timeinfo->tm_year = year - 1900;
	timeinfo->tm_mon = month - 1;
	timeinfo->tm_mday = day;
	timeinfo->tm_hour = h;
	timeinfo->tm_min = min;
	timeinfo->tm_sec = sec;

	/* Convert to GMT unixtimestamp */
	int unix_timestamp = timegm(timeinfo); 

	/* Add title to the output file */
	file << "TIMESTAMP" << "    " << "IP" << "           " << "CPU_ID" << "    " << "CPU_USAGE";

	/* To generate random number differently when executed each time */
	srand(time(NULL));

	/* Loop through every minute and log it to the file */
	for (int j = 0; j < TOTAL_NO_OF_MINUTES; j++)
	{
		/* Flags to set ip addresses */
		int ip_3 = 1;
		int ip_4 = 1;

		for (int i = 0; i < NO_OF_SERVERS; i++)
		{
			/* Save Current time */
			server[i].unix_timestamp = unix_timestamp;

			/* Save CPU_IDs */
			server[i].cpu_1 = 0;
			server[i].cpu_2 = 1;

			/*CPU usage.Just a random number*/
			server[i].cpu_usage_1 = rand() % 101;
			server[i].cpu_usage_2 = rand() % 101;

			/*Assign IP addresses to each server */
			server[i].ip[0] = 170;
			server[i].ip[1] = 145;
			
			/* To restrict ip address to not go beyond 255 */
			if (ip_4 <= 255)
			{
				server[i].ip[2] = ip_3;
				server[i].ip[3] = ip_4++;
			}
			else
			{
				ip_4 = 1;
				ip_3++;
				server[i].ip[2] = ip_3;
				server[i].ip[3] = ip_4++;
			}

			/* Log the saved values to output file */
			file << endl << server[i].unix_timestamp << "   ";
			file << server[i].ip[0] << "." << server[i].ip[1] << "." << server[i].ip[2] << "." << server[i].ip[3] << "    ";
			file << server[i].cpu_1 << "        " << server[i].cpu_usage_1 << "%" << endl;
			file << server[i].unix_timestamp << "   ";
			file << server[i].ip[0] << "." << server[i].ip[1] << "." << server[i].ip[2] << "." << server[i].ip[3] << "    ";
			file << server[i].cpu_2 << "        " << server[i].cpu_usage_2 << "%";
		}//End for

		/* Since we need to log every minute increment by 60s */
		unix_timestamp = unix_timestamp + 60;

	}//End for

	/* Free allocated Server memory */
	delete[] server;

	/* Close the file */
	file.close();

	cout << "File closed" << endl;
}
