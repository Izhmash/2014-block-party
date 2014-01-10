
task main()
{
	int min = 1000;
	int max = 6000;
  while(true)
  {
  	PlayTone((rand() % (max-min)) + min, 5);     //rand() % (max-min)) + min;
  }


}
