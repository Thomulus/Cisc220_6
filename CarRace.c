#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>

int notdone = 1;
int car1 = 0;
int car2 = 0;
int car3 = 0;
int car4 = 0;
int car5 = 0;
pthread_t threads[6];

void *humanwaiting(void *threadid){
	while(notdone){
		char enter = getchar();
		if (enter == '\n'){
			car1 +=1;
			if (car1 ==40){
				notdone = 0;
			}
		}
		//usleep();
		enter = 'a';
	}
}
void *drawing(void *threadid){
	printf("hello");
	while(notdone){
		printf("hello");
		usleep(1000);
		printf("HELLO EVERYONE %d",car1);
		usleep(200000);
	}
}
void *waiting(void *threadid){
	long tid;
	tid = (long) threadid;
	long double waittime = rand();
	waittime = (waittime/RAND_MAX)*1000000;
	usleep(waittime);
	//printf("%ld Waited %Le microseconds\n",tid, waittime);
	switch (tid){
		case 1:
			car1+=1;
			break;
		case 2:
			car2+=1;
			break;
		case 3:
			car3+=1;
			break;
		case 4:
			car4+=1;
			break;
		case 5:
			car5+=1;
			break;
	}
	if ((car1 <40) & (car2<40) & (car3<40) & (car4<40) & (car5<40)){
		int rc = pthread_create(threads+tid,NULL,waiting,(void*)tid);
	}
	else{
		notdone = 0;
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
	printf("car1: %d, car2: %d, car3: %d, car4: %d, car5: %d",car1,car2,car3,car4,car5);
	pthread_exit(NULL);
}
