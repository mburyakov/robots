int direction;

int nextR1(int r)
{
	      int nextRoute;
        switch (r)
        {
          case 1: nextRoute = 2; break;
          case 2: nextRoute = 8; break;
          case 8: nextRoute = 12; break;
          case 12: nextRoute = 16; break;
          case 16: nextRoute = 20; break;
          case 20: nextRoute = 21; break;
          case 21: nextRoute = 28; break;
          case 28: nextRoute = 25; break;
          case 25: nextRoute = 13; break;
          case 13: nextRoute = 14; break;
          case 14: nextRoute = 10; break;
          case 10: nextRoute = 5; break;
          case 5: nextRoute = 3; break;
          case 3: nextRoute = 8; break;
        }
	      return nextRoute;
}

int nextR2(int r)
{
	      int nextRoute;
        switch (r)
        {
          case 1: nextRoute = 7; break;
          case 7: nextRoute = 16; break;
          case 16: nextRoute = 19; break;
          case 19: nextRoute = 24; break;
          case 24: nextRoute = 30; break;
        }
	      return nextRoute;
}


int angleFromTo(int from, int to)
{
	switch (from*100+to)
	{
		case 0102:
		  direction = 11; return -100;
		  break;
		case 0107:
		  direction = 11; return 10;
		  break;

		case 0201:
		  return 90;
		  break;
		case 0207:
		  return -90;
		  break;
		case 0203:
		  direction = 11; return -10;
		  break;
		case 0208:
		  direction = 11; return 100;
		  break;

		case 0302:
		  return 10;
		  break;
		case 0308:
		  return -100;
		  break;
		case 0304:
		  return -90;
		  break;
		case 0305:
		  direction = 11; return 0;
		  break;
		case 0309:
		  direction = 11; return 90;
		  break;

		case 0403:
		  direction = 11; return 90;
		  break;
		case 0405:
		  direction = 11; return 90;
		  break;
		case 0409:
		  direction = 11; return 0;
		  break;

		case 0504:
		  return 90;
		  break;
		case 0509:
		  return -90;
		  break;
		case 0503:
		  return 0;
		  break;
		case 0506:
		  return -90;
		  break;
		case 0510:
		  direction = 11; return 90;
		  break;

		case 0605:
		  return 100;
		  break;
		case 0610:
		  direction = 11; return -10;
		  break;

		case 0701:
		  return -10;
		  break;
		case 0702:
		  return 100;
		  break;
		case 0711:
		  return 90;
		  break;
		case 0712:
		  direction = 11; return -90;
		  break;
		case 0716:
		  direction = 11; return 0;
		  break;

		case 0802:
		  return -90;
		  break;
		case 0803:
		  return 90;
		  break;
		case 0812:
		  return 100;
		  break;
		case 0817:
		  direction = 11; return -10;
		  break;

		case 0903:
		  return -90;
		  break;
		case 0904:
		  return 0;
		  break;
		case 0905:
		  return 90;
		  break;
		case 0913:
		  direction = 11; return 10;
		  break;
		case 0914:
		  return -100;
		  break;

		case 1006:
		  return 10;
		  break;
		case 1005:
		  return -100;
		  break;
		case 1018:
		  direction = 11; return 0;
		  break;
		case 1015:
		  return -90;
		  break;
		case 1014:
		  direction = 11; return 90;
		  break;

		case 1112:
		  direction = 11; return 0;
		  break;
		case 1107:
		  return -90;
		  break;
		case 1116:
		  direction = 11; return 90;
		  break;

		case 1216:
		  return -90;
		  break;
		case 1211:
		  return 0;
		  break;
		case 1207:
		  return 90;
		  break;
		case 1208:
		  return -90;
		  break;
		case 1217:
		  direction = 11; return 90;
		  break;

		case 1309:
		  return -10;
		  break;
		case 1314:
		  return 100;
		  break;
		case 1322:
		  return -90;
		  break;
		case 1325:
		  direction = 11; return 90;
		  break;

    case 1409:
		  return 90;
		  break;
    case 1413:
		  direction = 11; return -90;
		  break;
    case 1410:
		  return -90;
		  break;
    case 1418:
		  return 90;
		  break;
    case 1415:
		  return 0;
		  break;

    case 1510:
		  return 90;
		  break;
    case 1514:
		  direction = 11; return 0;
		  break;
    case 1518:
		  direction = 11; return -90;
		  break;

    case 1611:
		  return -90;
		  break;
    case 1607:
		  return 0;
		  break;
    case 1612:
		  return 90;
		  break;
    case 1619:
		  direction = 11; return 10;
		  break;
    case 1620:
		  direction = 11; return -100;
		  break;


    case 1708:
		  return 10;
		  break;
    case 1712:
		  return -100;
		  break;
    case 1720:
		  return 60;
		  break;
    case 1721:
		  direction = 11; return -60;
		  break;

    case 1810:
		  return 0;
		  break;
    case 1814:
		  return -90;
		  break;
    case 1815:
		  return 90;
		  break;

    case 1916:
		  return -10;
		  break;
    case 1920:
		  return 100;
		  break;
    case 1923:
		  return 100;
		  break;
    case 1924:
		  direction = 11; return -10;
		  break;

    case 2017:
		  return -60;
		  break;
    case 2021:
		  direction = 11; return 60;
		  break;
    case 2016:
		  return 90;
		  break;
    case 2019:
		  return -90;
		  break;

    case 2120:
		  return -60;
		  break;
    case 2117:
		  return 60;
		  break;
    case 2128:
		  direction = 11; return -60;
		  break;
    case 2127:
		  return 60;
		  break;

    case 2225:
		  direction = 11; return -10;
		  break;
    case 2213:
		  return 100;
		  break;

    case 2319:
		  return -90;
		  break;
    case 2324:
		  direction = 11; return 90;
		  break;

    case 2423:
		  return -100;
		  break;
    case 2419:
		  return 10;
		  break;
    case 2426:
		  return 90;
		  break;
    case 2430:
		  return 0;
		  break;
    case 2427:
		  direction = 11; return -90;
		  break;

    case 2522:
		  return 10;
		  break;
    case 2513:
		  return -100;
		  break;
    case 2531:
		  return 0;
		  break;
    case 2529:
		  return -90;
		  break;
    case 2528:
		  return 90;
		  break;

    case 2624:
		  return -90;
		  break;
    case 2630:
		  return 90;
		  break;
    case 2627:
		  direction = 11; return 0;
		  break;

    case 2728:
		  direction = 11; return 60;
		  break;
    case 2721:
		  return -60;
		  break;
    case 2724:
		  return 90;
		  break;
    case 2730:
		  return -90;
		  break;
    case 2726:
		  return 0;
		  break;

		case 2821:
		  return 60;
		  break;
		case 2827:
		  return -60;
		  break;
		case 2825:
		  return -90;
		  break;
		case 2831:
		  return 90;
		  break;
		case 2829:
		  return 0;
		  break;

		case 2925:
		  return 90;
		  break;
		case 2928:
		  return 0;
		  break;
		case 2931:
		  return -90;
		  break;

		case 3026:
		  return -90;
		  break;
		case 3024:
		  return 0;
		  break;
		case 3027:
		  direction = 11; return 90;
		  break;

		case 3129:
		  return 90;
		  break;
		case 3125:
		  return 0;
		  break;
		case 3128:
		  return -90;
		  break;

		default:
		  return -1;
		  break;
  }
}
