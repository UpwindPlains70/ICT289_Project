/*
* Solution for lab exercise
*	Smooths input image
*	Displays both input and processed image.

* shows basic concepts
* will need to modularise the code for reuse
*/

// If using MAC, compile as follows:
//  gcc Edge.c -framework GLUT -framework OpenGL -framework Cocoa -o Edge

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #include <gl/freeglut.h>        // For windows
#ifdef _WIN64
    //define something for Windows (64-bit only)
#endif
#elif __APPLE__
    #include <GLUT/glut.h>            // for Mac OS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define   MAXROW	256
#define   MAXCOL	256     /* handles 320x200 pixel images */

typedef 	unsigned char	pixel;       /* one byte (0 .. 255) for each pixel */
typedef	char	name[15];

typedef struct Image{
    int W,H;
    unsigned char* R;
    unsigned char* G;
    unsigned char* B;
};

/* image buffers used for display */
pixel	image_buf[MAXROW*MAXCOL][3];
pixel 	image[MAXROW][MAXCOL][3] ;   /* image arrays */
pixel	p;

name  	inf_name = "groupA.tga";           /* strings to store file names */
FILE	*inf_handle;    /*file handles created at file open */

int		charin;

/*************************************************************************/
void	InputImage(void)
{
	printf("Enter the name of the input file  : ");
   //gets(inf_name);

   /* try to open file for reading (r) in binary (b) mode */
   if  ((inf_handle = fopen(inf_name, "rb")) == NULL)  /* open failed */
    {
         puts("*** Can't open input file - please check file name typed!\n ");
         charin = getchar();
         exit(1);   /* terminate execution */
    }

   /* reaching this line of code means file opened successfully,
   now read file contents into image array */
  	for (int r = 0;  r < MAXROW; r++ )
      	for (int c = 0;  c < MAXCOL; c++)  {
            for(int i = 0; i < 3; i++){
                if((charin=fgetc(inf_handle))==EOF)   /* read failed */
                {
                  printf("***File reading failed! \n");
                  charin = getchar();
                  exit(1);    /* terminate execution */
                }
                image[r][c][i] = charin;
               // printf("loading");
            }
      	}

   /* reaching this line of code means all of file read successfully */
   printf("\nImage input completed!\n");
   fclose(inf_handle);    /* close input file  */
 }	/* end InputImage */

/*************************************************************************/

void	WriteCaptions(void)
 {
   int	i;
   char	caption1[ ] = "INPUT_IMAGE";   // 11 chars  + null  char
   char	caption2[ ] = "EDGE_DETECTED";  // 12 chars + null char
   //char	caption1[ ] = "original image";   //
   //char	caption2[ ] = "copy";

   glColor3f(0.0, 0.0, 0.0);

   glRasterPos2i(154, 20);
   for (i=0; i< sizeof(caption1); i++)
   	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption1[i]);

   glRasterPos2i(514, 20);
   for (i=0; i< sizeof(caption2); i++)
   	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, caption2[i]);
 }

void	Display(void)
{
   int	offset;

 /*flip image - 1st row becomes last - before calling glDrawPixels
to display original image*/
   offset = 0;
	for (int r = MAXROW-1;  r >= 0;  r-- )	{
      for (int c = 0;  c < MAXCOL; c++)
        for(int i = 0; i < 3; i++){
            image_buf[MAXCOL*offset + c][i] =  image[r][c][i];
        }
      offset++;
	}

   glClear(GL_COLOR_BUFFER_BIT);

/* switch matrix mode  to 'projection' */
	glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

/* set up an orthographic projection in 2D with a 760x280 viewing window  */
	gluOrtho2D(0.0,760.0, 0.0,280.0);

/* switch matrix mode back to 'model view' */
	glMatrixMode(GL_MODELVIEW);

   WriteCaptions();

/* set raster position for displaying image in graphics image buffer*/
   glRasterPos2i(40, 40);
/* load graphics image buffer with image from your own image buffer */
   glDrawPixels(MAXCOL, MAXROW, GL_RGB, GL_UNSIGNED_BYTE, image); //image_buf

   glFlush();
}
/*************************************************************************/

/*************************************************************************/
void  SetupDisplay(void)
{
   glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);

   glutInitWindowSize(760,280); /* 760 x 280 pixel graphics display window */

	glutInitWindowPosition(0,0); /* place window top left on display */

   glutCreateWindow("Image handler"); /* graphics window title */
	glClearColor(1.0, 1.0, 1.0, 1.0); /* set up to draw on white background */

   glutDisplayFunc(Display); /* register display callback function  */
}

/*********************************************************/
void	main(int argc, char** argv)
{
   glutInit(&argc, argv);

	InputImage();
	//glReadPixels(0,0,512,512,GL_RGB, GL_UNSIGNED_BYTE, myImage);
    //ProcessImage();
    //OutputImage();
    SetupDisplay();

   /*int bins;
   printf("Enter the number of bins for histogram : ");
   scanf("%d", &bins);

   printHistogram(bins, computeHistogram(bins, image, MAXROW, MAXCOL));
*/
   printf("\nPress Ctrl-c to end execution\n");
   glutMainLoop();


 }

