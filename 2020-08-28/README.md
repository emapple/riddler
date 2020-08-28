# [August 28, 2020](https://fivethirtyeight.com/features/can-you-cover-the-globe/)

This week's Riddler Express is a simple problem: if the world were covered by a sheet, how much area would you have to add in order to have the sheet raised 1 meter above the ground?

This is a slightly different take on the more common problem of a rope around the Earth, and how much length you have to add to raise it by 1 meter. Both cases are quite simple. In each case, you can simply find the difference between the area/circumference with a radius of $r+1$ and a radius of $r$.

For the rope:
$$r_1 - r_0 = 2\pi\,(r+1)-2\pi\,r =2\pi \approx 6.28\,\mathrm{m}^2$$
$$A_1 - A_0 = 4\pi\,(r+1)^2 - 4\pi\,r^2 = 8\pi\,r + 4\pi \approx 1.60\times10^8\,\mathrm{m}^2$$

The difference in area happens to be almost exactly the same as the area of Liechtenstein, according to Wikipedia.

My first approach is brute-force computational.
