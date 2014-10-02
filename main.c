#pragma config(Sensor, S1,     lightRight,     sensorLightActive)
#pragma config(Sensor, S3,     lightLeft,      sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "graph.c"

const short speed = 90;

const int robotN = 2;
const int master = 2 - robotN;

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
const int grayCriteria = 600;

const int lightLeftCorr = robotN == 1 ? 4 : -75;
const int lightRightCorr = robotN == 1 ? -13 : 60;

void lineFollow()
{
	switch (state) {
  case 2:

    int summary = (SensorRaw[lightLeft]-lightLeftCorr>grayCriteria) || (SensorRaw[lightRight]>grayCriteria);
    //nxtDisplayTextLine(1, "%d", SensorRaw[lightLeft]-lightAsymmetryCross);
    //nxtDisplayTextLine(2, "%d", SensorRaw[lightRight]);
    //nxtDisplayTextLine(3, "%d || %d = %d ", SensorRaw[lightLeft]-lightAsymmetryCross>grayCriteria, SensorRaw[lightRight]>grayCriteria, summary);
    if (!summary) {
      state = 3;
    }


		float err = SensorRaw[lightLeft] - lightLeftCorr - SensorRaw[lightRight] + lightRightCorr;
		errSum1 = (errSum1 * (sumTraceTime1*log(dt)-1) + err)/(sumTraceTime1*log(dt));
		errSum2 += err*dt;
		errSum2 = 0;
		float corr = (err+0*errSum1)/250.0+0*(err+0.0*errSum2)*(err+0.0*errSum2)*(err+0.0*errSum2)/80000.0;
	  motor[motorB] = speed*(1+corr);
	  motor[motorC] = speed*(1-corr);
	  break;
	default:
	  //should not be in this state
  }
}

int i;
//int routes[30] = {20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int routesMaster[7] = {18, 14, 9, 3, 2, 7, 0};
int routesSlave[14] = {16,20,17,8,3,9,13,25,28,21,20,19,23,0};

int routes[14] = {16,20,17,8,3,9,13,25,28,21,20,19,23,0};

int overlapMaster;
int overlapSlave;
int slaveWaiting;
int slaveBlocking;

int overlapsMaster[6] = {14, 2, 0, 0, 0, 0};
int overlapsSlave[6] = {3, 25, 0, 0, 0, 0};

void init() {
  overlapMaster = -1;
  overlapSlave = -1;
  slaveWaiting = 0;
  slaveBlocking = -1;
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

void printInt(word n)
{
	string s;
	StringFormat(s, "%d", n);
	nxtDisplayTextLine(1,s);
}

void waitIdle() {
  while(nMotorRunState[motorB] != runStateIdle || nMotorRunState[motorC] != runStateIdle ){}
}

void sleep() {
    motor[motorB] = 0;
    motor[motorC] = 0;
    wait1Msec(100);
}


void straight(int dist) {
    nMotorEncoder[motorB] = 0;
    nMotorEncoder[motorC] = 0;

    nMotorEncoderTarget[motorB] = dist;
    nMotorEncoderTarget[motorC] = dist;
    motor[motorB] = 100;
    motor[motorC] = 100;
    waitIdle();
    //nxtDisplayString(1, "%d", nMotorEncoder[motorB]);
    //nxtDisplayString(2, "%d", nMotorEncoder[motorC]);

  }

void turnDirection(int angle) {
  motor[motorB] = 0;
  motor[motorC] = 0;
  switch (angle)
  {
  	case 90:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 350;
  	  nMotorEncoderTarget[motorC] = 15;
      motor[motorB] = 100;
      motor[motorC] = 7;
      waitIdle();
      break;
  	case -90:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 15;
  	  nMotorEncoderTarget[motorC] = 350;
      motor[motorB] = 7;
      motor[motorC] = 100;
      waitIdle();
      break;
  	case 100:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 350;
  	  nMotorEncoderTarget[motorC] = 15;
      motor[motorB] = 100;
      motor[motorC] = 7;
      waitIdle();
      break;
  	case -100:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 15;
  	  nMotorEncoderTarget[motorC] = 350;
      motor[motorB] = 7;
      motor[motorC] = 100;
      waitIdle();
      break;
  	case 60:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 250;
  	  nMotorEncoderTarget[motorC] = 15;
      motor[motorB] = 100;
      motor[motorC] = 7;
      waitIdle();
      break;
  	case -60:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 15;
  	  nMotorEncoderTarget[motorC] = 250;
      motor[motorB] = 7;
      motor[motorC] = 100;
      waitIdle();
      break;
    case 10:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 50;
  	  nMotorEncoderTarget[motorC] = 10;
      motor[motorB] = 100;
      motor[motorC] = 20;
      waitIdle();
      break;
    case -10:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 10;
  	  nMotorEncoderTarget[motorC] = 50;
      motor[motorB] = 20;
      motor[motorC] = 100;
      waitIdle();
      break;
    case 0:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 100;
  	  nMotorEncoderTarget[motorC] = 100;
      motor[motorB] = 100;
      motor[motorC] = 100;
      waitIdle();
      break;
    default:
      //nothing here
  }
}

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

void masterDo() {
  nxtDisplayBigTextLine(6, "master");
  if (message == 0) { return; }
  for (int i = 0; i < 3; i++) {
    if (message == overlapsSlave[2*i]) {
      if (overlapMaster == 2*i) {
        slaveWaiting = 1;
        return;
      } else {
        slaveBlocking = message;
        sendMessage(1);
        return;
      }
    }
  }

  for (int i = 0; i < 3; i++) {
    if (message == overlapsSlave[2*i+1]) {
      if (overlapMaster == 2*i) {
        assert();
      } else {
        slaveBlocking = -1;
      }
    }
  }
  sendMessage(1);
  nxtDisplayBigTextLine(6, "send");
  //wait1Msec(5000);
  nxtDisplayBigTextLine(6, "    ");
  ClearMessage();
}

task main()
{

  init();

  //while (true) {
  //  nxtDisplayString(1, "waiting");
  //  while (message == 0) {}
  //  ClearMessage();
  //  sendMessage(1);
  //  nxtDisplayString(2, "sent");
  //}


  //while (true) {
  //  nxtDisplayTextLine(1,"l = %d",SensorRaw[lightLeft]);
  //  nxtDisplayTextLine(2,"r = %d",SensorRaw[lightRight]);
  //}

  /*while (true) {
    readData();
    nxtDisplayTextLine(1,"known = %d",routeIndex);
    nxtDisplayTextLine(2,"%d %d %d %d %d %d",routes[0],routes[1],routes[2],routes[3],routes[4],routes[5],routes[6]);
    wait1Msec(10)
  }*/


  while(true)                           // Infinite loop
  {
  	nxtDisplayTextLine(2,"state=%d",state);
  	nxtDisplayTextLine(3,"i=%d",i);
  	nxtDisplayTextLine(4,"ri=%d",routeIndex);
    timeInc();
    if (master) {
      masterDo();
    }
    //readData();
    switch (state)
    {
      case 1:
        motor[motorC] = 0;
        motor[motorB] = 0;
        if (routes[i+1])
        {
        	state = 3;
        }
        break;
      case 2:
        lineFollow();
        break;
      case 3:
        int nextRoute;
        /*do {
          nextRoute = random[31];
        } while (angleFromTo(route, nextRoute) == -1);*/
        if (routes[i+1]) {
        	i++;
          nextRoute = routes[i];

          nxtDisplayTextLine(5, "ol = %d", overlapMaster);


          nxtDisplayTextLine(2, "angle = %d", angleFromTo(route, nextRoute));
          turnDirection(angleFromTo(route, nextRoute));
          route = nextRoute;
          nxtDisplayTextLine(1, "route = %d", route);
          motor[motorB]=0;
          motor[motorC]=0;

          if (master) {
            if (overlapMaster == -1) {
              for (int i = 0; i < 3; i++) {
                if (nextRoute == overlapsMaster[2*i]) {
                  overlapMaster = i;
                }
              }
            } else {
              for (int i = 0; i < 3; i++) {
                if (nextRoute == overlapsMaster[2*i+1]) {
                  overlapMaster = -1;
                  if (slaveWaiting) {
                    sendMessage(1);
                    slaveWaiting = 0;
                  }
                }
              }
            }
          }

          if (!master) {
            sendMessage(nextRoute);
            nxtDisplayString(6, "waiting");
            while (!message == 1) {}
            nxtDisplayString(6, "receive");
            ClearMessage();
          }
          if (master) {
            if (slaveBlocking != -1) {
              while (overlapsMaster[2*slaveBlocking] == nextRoute) {
                masterDo();
                wait1Msec(10);
              }
            }
          }
          //sleep();
          state = 2;
        }
        else
        {
        	state = 1;
        }
        break;
    }
  }
}
