#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isInCube(float x, float y, float z, float centerX, float centerY, float centerZ, float alpha, float theta, float radius) {
	//trigonometry
	float cosTheta = cos(theta);
	float cosAlpha = cos(alpha);
	float sinTheta = sin(theta);
	float sinAlpha = sin(alpha);
	//get position relative to cube center
	float relativeX = x - centerX;
	float relativeY = y - centerY;
	float relativeZ = z - centerZ;
	//rotate the space to work with an orthogonl cube (using rotation matrices)
	float alignedX = relativeX * cosTheta * cosAlpha + relativeY * sinAlpha - relativeZ * sinTheta * cosAlpha;
	float alignedY = -relativeX * cosTheta * sinAlpha + relativeY * cosAlpha + relativeZ * sinTheta * sinAlpha;
	float alignedZ = relativeX * sinTheta + relativeZ * cosTheta;
	//simple check if point is in bounds of cube
	return -radius <= alignedX && alignedX <= radius && -radius <= alignedY && alignedY <= radius && -radius <= alignedZ && alignedZ <= radius;
}

void drawPixel(int flag, float x, float y, float z, float centerX, float centerY, float centerZ, float alpha, float theta, float radius, float maxZ, float deltaZ) {
	flag = 0;
	for (z = maxZ; z > 0.; z--) {
		if (flag == 0 && isInCube(x, y, z, centerX, centerY, centerZ, alpha, theta, radius)) {
			//draw character depending on proximity to camera
			flag = 1;
			char c = "@#&%{(?+<;:~-."[(int) ((maxZ - z) / deltaZ * 14.)];
			printf("%c%c", c, c);
		}
	}
	if (flag == 0)
		printf("  ");
}

int main() {
	//changeable values
	int side = 32;
	float radius = 8.;
	//initialization
	float alpha, theta = 0.;
	float centerXY = (float) side / 2.;
	float centerZ = 2. * radius;
	float maxZ = centerZ + sqrt(3) * radius;
	float minZ = centerZ - sqrt(2) * radius;
	float deltaZ = maxZ - minZ;
	float i, j, k;
	int flag;
	printf("\x1b[2J");
	while(true) {
		printf("\x1b[H");
		//draw cube
		for(i = 0.; i < side; i++) {
			for (j = 0.; j < side; j++)
				drawPixel(flag, i, j, k, centerXY, centerXY, centerZ, alpha, theta, radius, maxZ, deltaZ);
			printf("\n");
		}
		//rotate cube
		alpha += 0.0005;
		theta += 0.0008;
	}
	return 0;
}
