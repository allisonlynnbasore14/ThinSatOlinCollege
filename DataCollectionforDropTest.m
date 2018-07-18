% Takes accel, gyro, and mag data from LSM9DS1 Ardunio sensor via an SD
% and plots the x,y,and z values of each.

% Replace DATAVALS.TXT with the file from the SD card and run this file

fileName = 'DATAVALS.TXT';
pivot = 3; % number of items: accel, mag, gyro
A = importdata(fileName,' ');
A = A.textdata;
A = cell2table(A);
A = table2array(A);
time = zeros(round(size(A,1)/pivot),1);

dataVals = zeros(size(A));

for i = 1:size(A,1)
    time(i) = i;
end

for i = 1:size(A,1)
    for j = 1:size(A,2)
        dataVals(i,j) = str2double(A(i,j));
    end
end

figure  
plot(time,dataVals(:,2),time, dataVals(:,4),time, dataVals(:,6))
title('Accel Data')
legend('x','y','z')

figure
plot(time,dataVals(:,8),time, dataVals(:,10),time,dataVals(:,12))  
title('Mag Data')
legend('x','y','z')

figure
plot(time,dataVals(:,14),time, dataVals(:,16),time, dataVals(:,18))
title('Gyro Data')
legend('x','y','z')
