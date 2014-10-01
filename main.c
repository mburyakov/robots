#pragma config(Sensor, S1,     lightRight,     sensorLightActive)
#pragma config(Sensor, S3,     lightLeft,      sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "graph.c"

const short speed = 80;


int routeIndex;
int nextRoute0;
int nextRoute1;

long lastStepTime;

/*
states:
1 - waiting
2 - running route
3 - cross
*/
short state;

int route;

long startTime;
int dt;

float errSum1;
const int sumTraceTime1 = 10.0;
float errSum2;
const int grayCriteria = 500;
const int lightAsymmetryCorr = 30;
const int lightAsymmetryCross = -40;
void lineFollow()
{
	switch (state) {
  case 2:

    int summary = (SensorRaw[lightLeft]-lightAsymmetryCross>grayCriteria) || (SensorRaw[lightRight]>grayCriteria);
    //nxtDisplayTextLine(1, "%d", SensorRaw[lightLeft]-lightAsymmetryCross);
    //nxtDisplayTextLine(2, "%d", SensorRaw[lightRight]);
    //nxtDisplayTextLine(3, "%d || %d = %d ", SensorRaw[lightLeft]-lightAsymmetryCross>grayCriteria, SensorRaw[lightRight]>grayCriteria, summary);
    if (!summary) {
      state = 3;
    }


		float err = SensorRaw[lightLeft] + lightAsymmetryCorr - SensorRaw[lightRight];
		errSum1 = (errSum1 * (sumTraceTime1*log(dt)-1) + err)/(sumTraceTime1*log(dt));
		errSum2 += err*dt;
		errSum2 = 0;
		float corr = (err+0*errSum2)/100.0+0*(errSum1+0.0*errSum2)*(errSum1+0.0*errSum2)*(errSum1+0.0*errSum2)/80000.0;
	  motor[motorB] = speed*(1+corr);
	  motor[motorC] = speed*(1-corr);
	  break;
	default:
	  //should not be in this state
  }
}

int i;
int routes[30] = {20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//int routes[2] = {7,11};

void init() {
	i = 0;
	routeIndex = 0;
	nextRoute0 = routes[0];
	nextRoute1 = 0;
	route = routes[0];
  state = 2;
  wait1Msec(1000);
  startTime = nSysTime;
  lastStepTime = startTime;
}

void timeInc() {
	if (nSysTime - lastStepTime<10)
	{
		wait1Msec(10);
	}
	dt = nSysTime - lastStepTime;
	lastStepTime += dt;
}

void waitIdle(){
  while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle ){}
}

void printInt(word n)
{
	string s;
	StringFormat(s, "%d", n);
	nxtDisplayTextLine(1,s);
}

void turnInstant(int angle){

    switch (angle)
  {
  case 90:
  	  int a = 240;
    	nMotorEncoder[motorB] = 0;
    	nMotorEncoder[motorC] = 0;

      nMotorEncoderTarget[motorB] = a;
    	nMotorEncoderTarget[motorC] = a;
    	motor[motorB] = -100;
      motor[motorC] = 100;
      waitIdle();
      nxtDisplayString(1, "%d", nMotorEncoder[motorB]);
      nxtDisplayString(2, "%d", nMotorEncoder[motorC]);
      break;
  case 0:
       int c = 100;
     nMotorEncoder[motorB] = 0;
    	nMotorEncoder[motorC] = 0;

      nMotorEncoderTarget[motorB] = c;
    	nMotorEncoderTarget[motorC] = c;
    	motor[motorB] = 100;
      motor[motorC] = 100;
      waitIdle();
      nxtDisplayString(1, "%d", nMotorEncoder[motorB]);
      nxtDisplayString(2, "%d", nMotorEncoder[motorC]);
      break;
  case 180:
      int b = 470;
     nMotorEncoder[motorB] = 0;
    	nMotorEncoder[motorC] = 0;

      nMotorEncoderTarget[motorB] = b;
    	nMotorEncoderTarget[motorC] = b;
    	motor[motorB] = -100;
      motor[motorC] = 100;
      waitIdle();
      nxtDisplayString(1, "%d", nMotorEncoder[motorB]);
      nxtDisplayString(2, "%d", nMotorEncoder[motorC]);
      break;

  case -90:
  	  int d = 240;
    	nMotorEncoder[motorB] = 0;
    	nMotorEncoder[motorC] = 0;

      nMotorEncoderTarget[motorB] = d;
    	nMotorEncoderTarget[motorC] = d;
    	motor[motorB] = 100;
      motor[motorC] = -100;
      waitIdle();
      nxtDisplayString(1, "%d", nMotorEncoder[motorB]);
      nxtDisplayString(2, "%d", nMotorEncoder[motorC]);
      break;
    default:
      //nothing here
  }
}

// void turnDirection(int angle) {
  // switch (angle)
  // {
  	// case 90:
      // motor[motorB] = 100;
      // motor[motorC] = 0;
      // wait1Msec(1300);
      // break;
  	// case -90:
      // motor[motorC] = 100;
      // motor[motorB] = 0;
      // wait1Msec(1300);
      // break;
  	// case 100:
      // motor[motorB] = 100;
      // motor[motorC] = 0;
      // wait1Msec(1100);
      // break;
  	// case -100:
      // motor[motorC] = 100;
      // motor[motorB] = 0;
      // wait1Msec(1100);
      // break;
  	// case 60:
      // motor[motorB] = 100;
      // motor[motorC] = 0;
      // wait1Msec(700);
      // break;
  	// case -60:
      // motor[motorC] = 100;
      // motor[motorB] = 0;
      // wait1Msec(700);
      // break;
    // case 10:
      // motor[motorB] = 0;
      // motor[motorC] = 0;
      // //wait1Msec(1000);
      // motor[motorB] = 100;
      // motor[motorC] = 20;
      // wait1Msec(600);
      // motor[motorB] = 0;
      // motor[motorC] = 0;
      // //wait1Msec(1000);
      // motor[motorB] = 30;
      // motor[motorC] = 100;
      // wait1Msec(300);
      // motor[motorB] = 0;
      // motor[motorC] = 0;
      // //wait1Msec(1000);
      // break;
    // case -10:
      // motor[motorC] = 0;
      // motor[motorB] = 0;
      // //wait1Msec(1000);
      // motor[motorC] = 100;
      // motor[motorB] = 20;
      // wait1Msec(600);
      // motor[motorC] = 0;
      // motor[motorB] = 0;
      // //wait1Msec(1000);
      // motor[motorC] = 30;
      // motor[motorB] = 100;
      // wait1Msec(300);
      // motor[motorC] = 0;
      // motor[motorB] = 0;
      // //wait1Msec(1000);
      // break;
    // case 0:
      // motor[motorB] = 100;
      // motor[motorC] = 100;
      // wait1Msec(100);
      // break;
    // default:
      // //nothing here
  // }
// }

void readData()
{
  if (nextRoute1)
  {
  	nextRoute0 = nextRoute1;
  	int lft = nextRoute1/100;
  	int rgt = nextRoute1%100;
  	if ((rgt==routes[routeIndex]) || ((routeIndex>0)&&(rgt==routes[routeIndex-1])))
  	{

    }
  	else if (lft==routes[routeIndex])
    {
    	routeIndex++;
    	routes[routeIndex] = rgt;
    	nextRoute1 = 0;
    }
  	else if (angleFromTo(routes[routeIndex], lft)!=-1)
  	{
    	routeIndex++;
    	routes[routeIndex] = lft;
    	routeIndex++;
    	routes[routeIndex] = rgt;
    	nextRoute1 = 0;
    }
    else
    {
    	int med;
    	for (med = 1; med<40; med++) {
    		if ((angleFromTo(routes[routeIndex], med)!=-1) && (angleFromTo(med, lft)!=-1))
    		{
          routeIndex++;
          routes[routeIndex] = med;
          routeIndex++;
          routes[routeIndex] = lft;
          routeIndex++;
        	routes[routeIndex] = rgt;
    	    nextRoute1 = 0;
    	    break;
    	  }
    	}
    }
  }
}

task main()
{

  init();



    turnInstant(0);
    turnInstant(180);
    turnInstant(0);
    turnInstant(180);
    turnInstant(0);
    turnInstant(90);
    turnInstant(0);
    turnInstant(90);
    turnInstant(0);
    turnInstant(90);
    turnInstant(0);
    turnInstant(90);
    turnInstant(0);
    turnInstant(-90);
    turnInstant(0);
    turnInstant(-90);
    turnInstant(0);
    turnInstant(-90);
    turnInstant(0);
    turnInstant(-90);
    turnInstant(0);




  /*while (true) {
    readData();
    nxtDisplayTextLine(1,"known = %d",routeIndex);
    nxtDisplayTextLine(2,"%d %d %d %d %d %d",routes[0],routes[1],routes[2],routes[3],routes[4],routes[5],routes[6]);
    wait1Msec(10)
  }*/


  // while(true)                           // Infinite loop
  // {
  	// nxtDisplayTextLine(2,"state=%d",state);
  	// nxtDisplayTextLine(3,"i=%d",i);
  	// nxtDisplayTextLine(4,"ri=%d",routeIndex);
    // timeInc();
    // readData();
    // switch (state)
    // {
      // case 1:
        // motor[motorC] = 0;
        // motor[motorB] = 0;
        // if (routes[i+1])
        // {
        	// state = 3;
        // }
        // break;
      // case 2:
        // lineFollow();
        // break;
      // case 3:
        // int nextRoute;
        // /*do {
          // nextRoute = random[31];
        // } while (angleFromTo(route, nextRoute) == -1);*/
        // if (routes[i+1]) {
        	// i++;
          // nextRoute = routes[i];
          // nxtDisplayTextLine(2, "angle = %d", angleFromTo(route, nextRoute));
          // turnDirection(angleFromTo(route, nextRoute));
          // route = nextRoute;
          // nxtDisplayTextLine(1, "route = %d", route);
          // //motor[motorB]=0;
          // //motor[motorC]=0;
          // //wait1Msec(10000);
          // state = 2;
        // }
        // else
        // {
        	// state = 1;
        // }
        // break;
    // }
  // }
}
