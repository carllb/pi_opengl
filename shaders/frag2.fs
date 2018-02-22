#version 330 core

// Ouput data
out vec3 color;
in float frag_zoom;
in vec3 fragColor;

highp float plot( float x, float y);
highp float mag(float a, float b);

void main()
{

	// Output color = red
	highp float x = gl_FragCoord.x - 400;
	highp float y = gl_FragCoord.y - 300;

	//float r = sqrt(x*x + y*y);

	highp float r = plot(x/frag_zoom,y/frag_zoom);
	//color = fragColor;
	color = vec3(0,1,0);
}


float plot(highp float x, highp float y){
  x = x;
	y = y;
	highp float aTemp = 0;
	highp float bTemp = 0;
	highp float m = mag(aTemp,bTemp);
	for( int i =0; i< 100; i++){
		aTemp = aTemp*aTemp - bTemp*bTemp + x;
		bTemp = 2*aTemp*bTemp + y;
		m = mag(aTemp,bTemp);
		if ( m >= 2){
			return 1.0;
		}
	}

	return m/(2);

}

float mag(highp float a, highp float b){
	return sqrt(a*a + b*b);
}
