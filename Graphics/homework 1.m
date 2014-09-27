function [ output_args ] = untitled3( input_args )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
t=0:0.001:1;%Initializing time samples



s1=3*sin(2*pi*t);%Sine wave with amplitude=3unit
c1=3*cos(2*pi*t);%Cosine wave with amplitude=3unit

s2=2*sin(2*pi*t);
c2=2*cos(2*pi*t);

s3=1*sin(2*pi*t);
c3=1*cos(2*pi*t);

plot(s1,c1,s2,c2,s3,c3);%Plotting sin Vs Cos
grid on;%Enable grid lines



end

