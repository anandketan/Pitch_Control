# Pitch Control

The equations governing the motion of an aircraft are a set of six nonlinear coupled differential equations. However, under certain assumptions, they can be decoupled and linearized into longitudinal and lateral equations. Assuming that the aircraft is in steady-cruise at constant altitude and velocity; thus, the thrust, drag, weight and lift forces balance each other in the x- and y-directions. We will also assume that a change in pitch angle will not change the speed of the aircraft under any circumstance.

## PID Tuning

The process of tuning is done to ensure design meets the follwoing criteria: Overshoot less than 10%, rise time less than 2 seconds, settling time less than 10 seconds and steady-state error less than 2% of expected final value.

1. Proportional control - Root locus and Bode plot analysis gives us the following output, which is not satisfactory:

<img width="960" alt="proportional_ctrl" src="https://user-images.githubusercontent.com/72498471/97167782-6834bd80-17ad-11eb-9dae-afef581b4323.PNG">

2. Tuning the PID by changing values of Kp, Ki, Kd:

<img width="960" alt="gain_tuning" src="https://user-images.githubusercontent.com/72498471/97167757-5d7a2880-17ad-11eb-8f5e-82dfc4f16210.PNG">

3. Completed tuning of PID and obtained final Ki= 0.5241, Kp = 1.0482, and Kd = 0.5241:

<img width="960" alt="PID_fully_tuned" src="https://user-images.githubusercontent.com/72498471/97167793-6d920800-17ad-11eb-98c9-8e2dd689e908.PNG">

This response meets all of the given requirements as summarized below: Overshoot = 7.5% < 10%, steady-state error = 0% < 2%, settling time = 9.25 seconds < 10 seconds, rise time = 0.413 seconds < 2 seconds          
Therefore, this PID controller will provide the desired performance of the aircraft's pitch.

  

