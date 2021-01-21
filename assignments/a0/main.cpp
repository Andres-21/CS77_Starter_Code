//#####################################################################
// Main
// Dartmouth COSC 77/177 Computer Graphics, starter code
// Contact: Bo Zhu (bo.zhu@dartmouth.edu)
//#####################################################################
#include <iostream>

#include <random>
#include "Common.h"
#include "Driver.h"
#include "Particles.h"
#include "OpenGLMesh.h"
#include "OpenGLCommon.h"
#include "OpenGLWindow.h"
#include "OpenGLViewer.h"
#include "OpenGLMarkerObjects.h"
#include "OpenGLParticles.h"

/////////////////////////////////////////////////////////////////////
//// TODO: put your name in the string               
/////////////////////////////////////////////////////////////////////

const std::string author="Andres Hernandez";

/////////////////////////////////////////////////////////////////////
//// These are helper functions we created to generate circles and triangles by testing whether a point is inside the shape or not.
//// They can be used in the paintGrid function as "if the pixel is inside, draw some color; else skip."
//// You may create your own functions to draw your own shapes

//// The paintGrid function is implemented as a GLSL fragment shader. 
//// The GLSL grammar is C-style, and if you are curious about its full picture (which we will start to learn the details in Week 3), 
//// you may find more information on https://www.khronos.org/files/opengl43-quick-reference-card.pdf (Page 6 - 7 would probably be helpful!)
//// You don't need advanced GLSL features for this assignment (reading the starter code should be enough).
//// You can also test it (copy the whole string) in Shadertoy: https://www.shadertoy.com/new    
/////////////////////////////////////////////////////////////////////

const std::string draw_pixels = To_String(
const float M_PI = 3.1415926535; 

// The side length of the minimum unit (or the new "pixels")
const float PIXEL_SIZE = 2.; 

// To check if a point is inside a circle
bool inCircle(vec2 p, vec2 center, float radius) {
	vec2 to_center = p - center;
	if (dot(to_center, to_center) < radius * radius) {
		return true;
	}
	return false;
}

// To check if a point is inside a triangle
bool inTriangle(vec2 p, vec2 p1, vec2 p2, vec2 p3) {
	if (dot(cross(vec3(p2 - p1, 0), vec3(p - p1, 0)), cross(vec3(p2 - p1, 0), vec3(p3 - p1, 0))) >= 0. &&
		dot(cross(vec3(p3 - p2, 0), vec3(p - p2, 0)), cross(vec3(p3 - p2, 0), vec3(p1 - p2, 0))) >= 0. &&
		dot(cross(vec3(p1 - p3, 0), vec3(p - p3, 0)), cross(vec3(p1 - p3, 0), vec3(p2 - p3, 0))) >= 0.) {
		return true;
	}
	return false;
}

// To convert from Polar Coordinates to Cartesian coordinates
vec2 polar2cart(float angle, float length) {
	return vec2(cos(angle) * length, sin(angle) * length);
}

/////////////////////////////////////////////////////////////////////////
// Feel free to add more functions if needed!                          
/////////////////////////////////////////////////////////////////////////

/*
* Function: inEllipse
* Description: Determines whether a point is inside an ellipse rotated about an angle
*
* Params:
* [in] poi: Point of interest
* [in] center: The Center of the ellipse
* [in] s_radius: The shorter radius
* [in] l_radius: The longer radius
* [in] angle: The angle about which the ellipse is rotated
*
* Returns: True if the point is inside the ellipse. False if not.
*/
bool inEllipse(vec2 poi, vec2 center, float s_radius, float l_radius, float angle) {
	float num1 = pow(cos(angle) * (poi.x - center.x) + sin(angle) * (poi.y - center.y), 2.);
	float num2 = pow(sin(angle) * (poi.x - center.x) + cos(angle) * (poi.y - center.y), 2.);
	float den1 = pow(s_radius, 2.);
	float den2 = pow(l_radius, 2.);


	if ((num1 / den1) + (num2 / den2) <= 1.) {
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////
// TODO: replace the code below with your own code                 //
// Useful variables:											   //
// iTime: the passed seconds from the start of the program         //
// iResolution: the size of the window (default: 1280*960)         //
/////////////////////////////////////////////////////////////////////

// Return the rgba color of the grid at position (x, y) 
vec4 paintGrid(float x, float y) {
	vec2 center = vec2(iResolution / PIXEL_SIZE / 2.); // window center
	vec2 low_center = vec2(center.x, center.y - 75.); // window lower center
	vec2 cup_center = vec2(center.x, center.y + 60.); // cup center

	// Colors used for the image
	vec4 lightest_blue = vec4(vec3(210, 223, 255) / 255., 1.); // Lightest blue in image
	vec4 med_blue = vec4(vec3(174, 195, 249) / 255., 1.); // Medium shade of blue in image
	vec4 darkest_blue = vec4(vec3(144, 157, 191) / 255., 1.); // Darkest shade of blue in image
	vec4 background_color = vec4(vec3(234, 193, 193) / 255., 1.); // Background color
	vec4 black_color = vec4(vec3(0, 0, 0) / 255., 1.); // Black color
	vec4 white_color = vec4(vec3(250, 250, 250) / 255., 1.); // White color
	vec4 liquid_color = vec4(vec3(64, 48, 40) / 255., 1.); // Liquid color
	vec4 cookie_color = vec4(vec3(169, 135, 107) / 255., 1.); // Cookie color

	// Chocolate chip 1
	if (inEllipse(vec2(x, y), vec2(low_center.x - 70., low_center.y - 45.), 10., 5., -M_PI / 45.)) {
		return liquid_color;
	}
	// Chocolate chip 2
	if (inEllipse(vec2(x, y), vec2(low_center.x - 140., low_center.y - 25.), 11., 5., M_PI / 20.)) {
		return liquid_color;
	}
	// Chocolate chip 3
	if (inEllipse(vec2(x, y), vec2(low_center.x - 110., low_center.y - 45.), 12., 6., M_PI / 45.)) {
		return liquid_color;
	}
	// Chocolate chip 4
	if (inEllipse(vec2(x, y), vec2(low_center.x - 160., low_center.y + 20.), 10., 5., M_PI / 1.)) {
		return liquid_color;
	}
	// Chocolate chip 5
	if (inEllipse(vec2(x, y), vec2(low_center.x - 180., low_center.y), 10., 5., -M_PI / 45.)) {
		return liquid_color;
	}
	// Chocolate chip 6
	if (inEllipse(vec2(x, y), vec2(low_center.x - 90., low_center.y - 20.), 10., 5., M_PI / 1.)) {
		return liquid_color;
	}
	// Chocolate chip 7
	if (inEllipse(vec2(x, y), vec2(low_center.x - 130., low_center.y + 10.), 10., 5., M_PI / 55.)) {
		return liquid_color;
	}
	// Cookie 1
	else if (inEllipse(vec2(x, y), vec2(low_center.x - 100., low_center.y - 40.), 60., 35., M_PI / 45.)) {
		return cookie_color;
	}
	// Cookie 1 outline
	else if (inEllipse(vec2(x, y), vec2(low_center.x - 100., low_center.y - 38.), 60., 35., M_PI / 45.)) {
		return liquid_color;
	}
	// Cookie 2
	else if (inEllipse(vec2(x, y), vec2(low_center.x - 150., low_center.y), 60., 30., M_PI / 55.)) {
		return cookie_color;
	}
	// Cookie 2 outline
	else if (inEllipse(vec2(x, y), vec2(low_center.x - 150., low_center.y - 2.), 60., 30., M_PI / 55.)) {
		return liquid_color;
	}
	// Liquid
	else if (inEllipse(vec2(x, y), vec2(cup_center.x, cup_center.y + 15.), 120., 35., 0.)) {
		return liquid_color;
	}
	// Back of Inner Lip
	else if (inEllipse(vec2(x, y), vec2(cup_center.x, cup_center.y + 20.), 120., 40., 0.)) {
		return darkest_blue;
	}
	// Cup lip
	else if (inEllipse(vec2(x, y), vec2(cup_center.x, cup_center.y + 10.), 130., 55., 0.)) {
		return lightest_blue;
	}
	// Erase upper ellipse
	else if (inTriangle(vec2(x, y), vec2(0., cup_center.y + 10.), vec2(cup_center.x * 3., cup_center.y + 10.), vec2(cup_center.x, cup_center.y * 4.))) {
		return background_color;
	}
	// Cup body
	else if (inEllipse(vec2(x, y), cup_center, 150., 130., M_PI / 2.)) {
		return lightest_blue;
	}
	// Cup handle negative 
	else if (inCircle(vec2(x, y), vec2(cup_center.x + 132., cup_center.y - 40.), 38.)) {
		return background_color;
	}
	// Cup handle shadow 
	else if (inCircle(vec2(x, y), vec2(cup_center.x + 132., cup_center.y - 38.), 41.)) {
		return darkest_blue;
	}
	// Cup handle body
	else if (inCircle(vec2(x, y), vec2(cup_center.x + 130., cup_center.y - 40.), 50.)) {
		return lightest_blue;
	}
	// Dish inner outline
	else if (inEllipse(vec2(x, y), low_center, 100., 40., 0.)) {
		return darkest_blue;
	}
	// Dish second outer outline
	else if (inEllipse(vec2(x, y), low_center, 190., 70., 0.)) {
		return med_blue;
	}
	// Dish outer outline
	else if (inEllipse(vec2(x, y), low_center, 200., 80., 0.)) {
		return lightest_blue;
	}
	// Background color
	else {
		return background_color;
	}
}

// The function called in the fragment shader
void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
	// To divide the screen into the grids for painting!
	fragColor = paintGrid(floor(fragCoord.x / PIXEL_SIZE), floor(fragCoord.y / PIXEL_SIZE));
}

);

class A0_Driver : public Driver, public OpenGLViewer
{
	OpenGLScreenCover* screen_cover = nullptr;
	clock_t startTime = clock();

public:
	virtual void Initialize()
	{
		OpenGLViewer::Initialize();
	}

	//// Initialize the screen covering mesh and shaders
	virtual void Initialize_Data()
	{
		OpenGLShaderLibrary::Instance()->Create_Screen_Shader(draw_pixels, "shaderToy");
		screen_cover = Add_Interactive_Object<OpenGLScreenCover>();
		Set_Polygon_Mode(screen_cover, PolygonMode::Fill);
		Uniform_Update();

		screen_cover->Set_Data_Refreshed();
		screen_cover->Initialize();
		screen_cover->Add_Shader_Program(OpenGLShaderLibrary::Get_Shader("shaderToy"));
	}

	//// Update the uniformed variables used in shader
	void Uniform_Update()
	{
		screen_cover->setResolution((float)Win_Width(), (float)Win_Height());
		screen_cover->setTime(GLfloat(clock() - startTime) / CLOCKS_PER_SEC);
	}

	//// Go to next frame 
	virtual void Toggle_Next_Frame()
	{
		Uniform_Update();
		OpenGLViewer::Toggle_Next_Frame();
	}

	////Keyboard interaction
	virtual void Initialize_Common_Callback_Keys()
	{
		OpenGLViewer::Initialize_Common_Callback_Keys();
	}

	virtual void Run()
	{
		OpenGLViewer::Run();
	}
};

int main(int argc,char* argv[])
{
	if(author==""){std::cerr<<"***** The author name is not specified. Please put your name in the author string first. *****"<<std::endl;return 0;}
	else std::cout<<"Assignment 0 demo by "<<author<<" started"<<std::endl;

	A0_Driver driver;
	driver.Initialize();
	driver.Run();	
}

