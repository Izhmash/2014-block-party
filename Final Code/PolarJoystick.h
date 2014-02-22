//unfinished

float getMagnitude(float X, float Y)
{
	return sqrt(pow(X, 2) + pow(Y, 2));
}

float getDirRads(float X, float Y)
{
	return atan2(Y, X);
}

float getDirDegrees(float X, float Y)
{
	return (180/acos(-1))*getDirRads(X, Y);
}
