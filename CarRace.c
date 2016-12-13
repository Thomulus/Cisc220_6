#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>

int notdone = 1;
int cars[5];
pthread_t threads[6];

void *humanwaiting(void *threadid){
	while(notdone){
		char enter = getchar();
		if (enter == '\n'){
			cars[1] +=1;
			if (cars[1] >=40){
				notdone = 0;
			}
		}
		//usleep();
		enter = 'a';
	}
}
void *drawing(void *threadid){
	while(notdone){
		FILE * f = fopen("temp.txt","w");
		for (int car = 1; car < 6; car++){
			for (int i = 0; i < cars[car]; i++){
				fprintf(f,"~");
			}
			fprintf(f,"|->");
			for (int i = 0; i < 40- cars[car]; i++){
				fprintf(f," ");
			}
			fprintf(f,"# Lane %d #\n", car);
		}
		fclose(f);
		system("clear");
		system("echo 'Welcome to CISC220 Racing Arena'");
		system("echo 'Hit Enter to move forward\n'");
		system ("cat temp.txt");
		usleep(200000);
		//int rc;
		//rc = pthread_create(threads+1,NULL,humanwaiting,(void*)tid);
		system("rm temp.txt");
	}
}
void *waiting(void *threadid){
	long tid;
	tid = (long) threadid;
	long double waittime = rand();
	waittime = (waittime/RAND_MAX)*1000000;
	usleep(waittime);
	//printf("%ld Waited %Le microseconds\n",tid, waittime);
	cars[tid]+=1;
	if ((cars[1] <40) & (cars[2]<40) & (cars[3]<40) & (cars[4]<40) & (cars[5]<40)){
		int rc = pthread_create(threads+tid,NULL,waiting,(void*)tid);
	}
	else{
		notdone = 0;
		for (int i =1; i <6; i ++){
			pthread_cancel(threads[i]);
		}
	}
	pthread_exit(NULL);
}
int main(){
	time_t ct;
	srand((unsigned) time(&ct));
	printf("%d\n", RAND_MAX);
	long t;
	int rc;
	rc = pthread_create(threads+1, NULL, humanwaiting, (void*)1);
	if (rc){
		exit(-1);
	}
	rc = pthread_create(threads,NULL, drawing,(void*)0);
	for (t = 2; t<6; t++){
		rc = pthread_create(threads+t,NULL, waiting,(void*)t);
		if (rc){
			printf("derp");
			exit(-1);
		}
	}
	for(t = 0; t<6; t++){
		pthread_join(threads[t],NULL);
	}
	while (notdone){
	}
	rc = pthread_create(threads,NULL,drawing, (void*)0);
	printf("car1: %d, car2: %d, car3: %d, car4: %d, car5: %d\n",cars[1],cars[2],cars[3],cars[4],cars[5]);
	for (int i =1; i<6;i++){
		if (cars[i] >= 40){
			printf("Player %d WINS!", i);
		}
	}
	pthread_exit(NULL);
}
