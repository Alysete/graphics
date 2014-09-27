function [ output_args ] = untitled5( input_args )

t = linspace(0,10*pi,200);
x = t.*cos(t)/(10*pi)*0.5;
y = t.*sin(t)/(10*pi)*0.5;
plot(x,y,'-')
end

