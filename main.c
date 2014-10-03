#pragma config(Sensor, S1,     lightRight,     sensorLightActive)
#pragma config(Sensor, S3,     lightLeft,      sensorLightActive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "graph.c"

const short speed = 50;

const int robotN = 1;
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
const int lightRightCorr = robotN == 1 ? -13 : 47;

void lineFollow()
{
	switch (state) {
  case 2:

    int summary = (SensorRaw[lightLeft]-lightLeftCorr>grayCriteria) || (SensorRaw[lightRight]>grayCriteria);
    ////nxtDisplayTextLine(1, "%d", SensorRaw[lightLeft]-lightAsymmetryCross);
    ////nxtDisplayTextLine(2, "%d", SensorRaw[lightRight]);
    ////nxtDisplayTextLine(3, "%d || %d = %d ", SensorRaw[lightLeft]-lightAsymmetryCross>grayCriteria, SensorRaw[lightRight]>grayCriteria, summary);
    if (!summary) {
      state = 3;
    }


		float err = SensorRaw[lightLeft] - lightLeftCorr - SensorRaw[lightRight] + lightRightCorr;
		errSum1 = (errSum1 * (sumTraceTime1*log(dt)-1) + err)/(sumTraceTime1*log(dt));
		errSum2 += err*dt;
		errSum2 = 0;
		float corr = (err+0*errSum1)/200.0+0*(err+0.0*errSum2)*(err+0.0*errSum2)*(err+0.0*errSum2)/80000.0;
	  motor[motorB] = speed*(1+corr);
	  motor[motorC] = speed*(1-corr);
	  break;
	default:
	  //should not be in this state
  }
}

int i;
//int routes[30] = {20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int routesMaster[30] = {13, 25, 28, 21, 17,  8,  3,  9,         0,0,    0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};
int routesSlave[30]  = {12, 7,  2,  8,  12, 16, 19, 24, 27, 21, 17,     0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};

int routes[30] = {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0};

int overlapMaster;
int overlapSlave;
int slaveBlocking;

int overlapsMaster[6] = {17, 3, 28, 8, 0, 0};
int overlapsSlave[6] = {2, 12, 27, 12, 0, 0};

void skipMessages() {
  while (message != 0) {
    nxtDisplayTextLine(6, "skippig");
    ClearMessage();
  }
}


void init() {
  for (int i = 0; i<30; i++) {
    if (master) {
      routes[i] = routesMaster[i];
    } else {
      routes[i] = routesSlave[i];
    }
  }
  skipMessages();
  overlapMaster = -1;
  overlapSlave = -1;
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
	//nxtDisplayTextLine(1,s);
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
  	  nMotorEncoderTarget[motorB] = 100;
  	  nMotorEncoderTarget[motorC] = 20;
      motor[motorB] = 100;
      motor[motorC] = 10;
      waitIdle();
      break;
    case -10:
  	  nMotorEncoder[motorB] = 0;
  	  nMotorEncoder[motorC] = 0;
  	  nMotorEncoderTarget[motorB] = 10;
  	  nMotorEncoderTarget[motorC] = 100;
      motor[motorB] = 10;
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
  if (message == 0) { return; }
  nxtDisplayTextLine(6, "RECEIVED");
  int msg = message;
  ClearMessage();
  for (int i = 0; i < 3; i++) {
    if (msg == overlapsSlave[2*i]) {
      if (overlapMaster == i) {
        nxtDisplayTextLine(6, "deny %d", msg);
        return;
      } else {
        slaveBlocking = i;
        sendMessage(msg);
        nxtDisplayTextLine(6, "allow %d", msg);
        return;
      }
    }
  }


  for (int i = 0; i < 3; i++) {
    if (msg == overlapsSlave[2*i+1]) {
      slaveBlocking = -1;
    }
  }
  sendMessage(msg);
  nxtDisplayTextLine(6, "allow %d", msg);
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
    //nxtDisplayTextLine(1,"known = %d",routeIndex);
    //nxtDisplayTextLine(2,"%d %d %d %d %d %d",routes[0],routes[1],routes[2],routes[3],routes[4],routes[5],routes[6]);
    wait1Msec(10)
  }*/


  while(true)                           // Infinite loop
  {
  	nxtDisplayTextLine(1,"ovMast %d",overlapMaster);
  	nxtDisplayTextLine(2,"slBl %d",slaveBlocking);
  	nxtDisplayTextLine(3,"ovSl",overlapSlave);
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
        } else {
          i = 0;
        }
        nextRoute = routes[i];
          //nxtDisplayTextLine(5, "ol = %d", overlapMaster);


          //nxtDisplayTextLine(2, "angle = %d", angleFromTo(route, nextRoute));
          turnDirection(angleFromTo(route, nextRoute));
          route = nextRoute;
          //nxtDisplayTextLine(1, "route = %d", route);
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
                }
              }
            }
          }

          if (!master) {
            skipMessages();
            while (message != nextRoute) {
              skipMessages();
              sendMessage(nextRoute);
              nxtDisplayString(6, "wting %d", nextRoute);
              wait1Msec(100);
            }
            nxtDisplayString(6, "recv %d", message);
          }
          if (master) {
            while (slaveBlocking != -1 && slaveBlocking == overlapMaster) {
              masterDo();
              wait1Msec(10);
            }
          }
          //sleep();
          state = 2;
        break;
    }
  }
}
