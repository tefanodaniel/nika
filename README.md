### AVAILABLE FUNCTIONS
Below is a list of all the editing functions available in Nika:

- `swap [image_filename]` - ???  
- `crop [x1 y1] [x2 y2]` - crop an image to pixel range from (x1,y1) to (x2,y2)  
- `blackout [x y]` - black out (turn to black) an image up to pixel coordinate (x,y)  
- `grayscale` - convert a color image to grayscale  
- `contrast [double_value]` - increase or reduce the contrast by a double factor  

### HOW TO COMPILE & EXECUTE

To compile executable, run the command `make project`.
Afterwards, execute program as usual (ex: `./make project ARG1 ARG2 ...`)

### HOW TO USE

The order of command line arguments is as follows: 

input_filename, output_filename, operation, [arg1, arg2]

For example, to turn "cat.ppm" into a grayscale image and save the result to "cat-edited-gray.ppm":

`./project cat.ppm cat-edited-grey.ppm grayscale`

Another example, this time using the crop feature to crop "cat.ppm" to the pixel range
between (30,30) and (75,100) (and save the resulting image as "cropped-cat.ppm") 

`./project cat.ppm cropped-cat.ppm crop 30 30 75 100`

At the very top of this README is a *comprehensive* list of all editing functions available in Nika.

## Happy editing!

This utility was made by Stefano Tusa (stusa2@jhu.edu) as the midterm project for CS220 Intermediate Programming.


