#include "Graph3DAxis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <GL/glu.h>
#include <math.h>

#define PI 3.141592

Graph3DAxis::Graph3DAxis(int x,int y,int w,int h,const char *l)
            : Fl_Gl_Window(x,y,w,h,l)
{
        // Not sure yet what these do
        x = 0.0;
        y = 0.0;
        z = 0.0;
        t_x = 0.0;
        t_y = 0.0;
        t_z = 0.0;
        
        // Location of the camera
        camera_position[0] = 0.0;
        camera_position[1] = 0.0;
        camera_position[2] = 12.0;
        
        // Direction the camera is focused
        camera_direction[0] = 0.0;
        camera_direction[1] = 0.0;
        camera_direction[2] = -1.0;
        
        // Orientation of "up" in the camera viewing frame
        up_direction[0] = 0.0;
        up_direction[1] = 1.0;
        up_direction[2] = 0.0;
        
        width = 20;
        height = 20;
        font = 2;
        
        // Define the base pose
        base_pose[0] = 0.0;
        base_pose[1] = 0.0;
        base_pose[2] = 0.0;
        base_pose[3] = 0.0;
        base_pose[4] = 0.0;
        base_pose[5] = 0.0;
        
        // Define the color for the base axes (white)
        base_color[0] = 1.0;
        base_color[1] = 1.0;
        base_color[2] = 1.0;
        base_size = 2.0;
        
        // Define the default Maglev pose
        axis_pose[0] = 0.0;
        axis_pose[1] = 0.0;
        axis_pose[2] = 0.0;
        axis_pose[3] = 0.0;
        axis_pose[4] = 0.0;
        axis_pose[5] = 0.0;
        
        // Define the color for the axes that represent the MLHD
        axis_color[0] = 0.2;
        axis_color[1] = 0.2;
        axis_color[2] = 0.9; 
        axis_size = 1.0;
        
        // Indicate that the Maglev is not yet on
        flag_maglev_position = false;
}//Graph3DAxis

void 
Graph3DAxis::draw()
{
        // 
        if (!valid())
        {
                // Set the Projection Frame parameters
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
                
                // Set the Model View parameters
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
                
                // Determine the viewing location/orientation
                gluLookAt(camera_position[0], camera_position[1], camera_position[2],
                        camera_direction[0], camera_direction[1], camera_direction[2],
                        up_direction[0], up_direction[1], up_direction[2]);
        }
        
        // Clear the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Set the background color to black
        //glColor3f(0.0, 0.0, 0.0);
        
        // Debugging
        //printf("Updating: ");
        
        // Draw the axes
        glPushMatrix();
                // Draw the base axes in the appropriate color
                drawAxes(base_pose, base_color, base_size, true);
                
                // Draw the current position axes in the appropriate color
                drawAxes(axis_pose, axis_color, axis_size, false);
        glPopMatrix();
}//draw


void
Graph3DAxis::set3DAxis(double pose[6])
{
        double scale_position = 10000.0;
        double scale_rotation = 10.0;
        //printf("(%6.3f)", pose[2]);
        for (int dirIdx = 0; dirIdx < 3; dirIdx++)
        {
                axis_pose[dirIdx] = pose[dirIdx]*scale_position;
                axis_pose[dirIdx+3] = pose[dirIdx+3]*scale_rotation;
        }
}//get3DAxis


void
Graph3DAxis::drawAxes(float pose[6], float color[3], float size, bool base_frame)
{
        // Declare local variables
        void *font = GLUT_STROKE_ROMAN;
        float length = 10.0;
        
        // Extract the current parameters
        glPushMatrix();
        
                // Set the color to the input
                glColor3f(color[0], color[1], color[2]);
                
                // Set the line width to the appropriate size
                glLineWidth(size);
                
                // Translate the new axes to the correct location
                if (base_frame)
                {
                        glTranslatef(pose[0], pose[1], 0.0);
                }
                else
                {
                        glTranslatef(pose[0]/10.0, pose[1]/10.0, 0.0);
                        glRotatef(pose[5], 0.0, 0.0, 1.0);
                }
                
                // Draw the x-axis
                glBegin(GL_LINES);
                        glVertex3f(0.0, 0.0, 0.0);
                        glVertex3f(length, 0.0, 0.0);
                glEnd();
                
                // Draw the y-axis
                glBegin(GL_LINES);
                        glVertex3f(0.0, 0.0, 0.0);
                        glVertex3f(0.0, length, 0.0);
                glEnd();
                
        // Replace the original parameters
        glPopMatrix();
        
        // Change to the color red for the labels and boundary circle
        glColor3f(1.0, 0.0, 0.0);
        if (base_frame)
        {
                // For the base frame, draw the text labels of the axes
                
                // Draw the text "X"
                glPushMatrix();
                        glTranslatef(length, 0.0, 0.0);
                        glScalef(0.01, 0.01, 1.0);
                        glutStrokeCharacter(font, 'X');
                glPopMatrix();        
                
                // Draw the text "Y"
                glPushMatrix();
                        glTranslatef(0.0, length, 0.0);
                        glScalef(0.01, 0.01, 1.0);
                        glutStrokeCharacter(font, 'Y');
                glPopMatrix();
        }
        else
        {
                // For the non-base frame, draw the circle that
                //   represents the Maglev boundary at this height
                
                // Calculate the radius
                float radius = sqrt(144.0 - pose[2]*pose[2]/100.0);
                
                // Draw the circle
                glPushMatrix();
                        glLineWidth(1.0);
                        glBegin(GL_LINES);
                                float theta = 0.0;
                                float delta_theta = PI/12.0;
                                glVertex3f(radius*cos(theta), radius*sin(theta), 0.0);
                                while (theta < 2.0*PI)
                                {
                                        glVertex3f(radius*cos(theta+delta_theta), radius*sin(theta+delta_theta), 0.0);
                                        theta += delta_theta;
                                        glVertex3f(radius*cos(theta), radius*sin(theta), 0.0);
                                }
                                glVertex3f(radius*cos(theta+delta_theta), radius*sin(theta+delta_theta), 0.0);
                        glEnd();
                glPopMatrix();
        }
}//draw3DAxis

