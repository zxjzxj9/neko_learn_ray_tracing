# Big Neko Learns Ray Tracing


This is a tutorial project created by a big cat (me) in order to learn ray tracing.

## **Chapter 0.** How to create a figure.

This library is in RenderLib, with function to create a binary .ppm(P6) format. Following is an example of library generated by RenderLib. This is a circle in the square, with 256x256 pixel. This lib will be the basis of following ray tracing code.

![test.png](./RenderLib/test.png)

## **Chapter 1.** How to render a sphere.

First we need to build a background imag, the background is gradually changing from blue to white, which looks like follows (the image is *400 pixels* height x *800 pixels* width).
![background.png](./Chapter1/background.png)

Now that we have the background image, we can draw a sphere on the basis of it. The equation to describe a sphere looks like follows. 

$$ (\mathbf{r} - \mathbf{r_c})^2 = r^2 $$

where $ \mathbf{r_c} = (x_c, y_c, z_c) $ being the coordinate of sphere cneter, and $r$ being the radius of sphere. A ray is a straight line, so it shall have the equestion of 

$$ \mathbf{r }= \mathbf{r_0} + \mathbf{v} \cdot t$$

where $r = (x, y, z)$, $r_0$ is the starting point of the ray, $\mathbf{v}$ is the direction of the ray and $t$ a parameter describing the running of points on the straight line. With the two equations, it can be easily found that $t$ should satisfy (by constraining $v^2=1$):

$$(\mathbf{r_0}-\mathbf{r_c})^2 +2(\mathbf{r_0}-\mathbf{r_c})\cdot \mathbf{v} \cdot t + t^2 = r^2$$

We can simply judge if the ray has hit the surface by the following variable:

$$ \Delta = 4(\mathbf{r_0}-\mathbf{r_c})^2 - 4*[(\mathbf{r_0}-\mathbf{r_c})^2 - r^2]$$

We have hit, tangent to and away from sphere 3 situations, correponding to $ \Delta >0, \Delta =0, \Delta <0$ three cases.
