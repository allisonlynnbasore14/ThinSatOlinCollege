fileName = 'DATAVALS.TXT';
pivot = 3; % number of items: accel, mag, gyro
A = importdata(fileName,' ');
A = A.textdata;
A = cell2table(A);
A = table2array(A)
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




% 
% accel = zeros(round(size(A,1)/pivot),3); % in x,y,z order
% mag = zeros(round(size(A,1)/pivot),3); % Magnetometer in x,y,z order
% gyro = zeros(round(size(A,1)/pivot),3); % in x,y,z order
% time = zeros(round(size(A,1)/pivot),1);
% allData = [accel,mag,gyro,time];
% 
% typeCount = 1;
% aIndex= 1;
% mIndex=1;
% gIndex=1;
% test = getXYZvals(A(1,:))
% for i = 1:size(A,1)
%     if(typeCount == 1)
% %        for j = 1:size(A,2)
% %            %accel(aIndex,j) = A(i,j);
% %        end
%        [Ax,Ay,Az,Mx,My,Mz,Gx,Gy,Gz] = getXYZvals(A(i,:));
%        accel(aIndex,1) = x;
%        accel(aIndex,2) = y;
%        accel(aIndex,3) = z;
%        time(aIndex,1) = aIndex;
%        aIndex = aIndex +1;
%     end
%     if(typeCount == 2)
%        for j = 1:size(A,2)
%            %mag(mIndex,j) = A(i,j);
%        end
%        mIndex = mIndex +1;
%     end
%     if(typeCount == 3)
%        for j = 1:size(A,2)
%            %gyro(gIndex,j) = A(i,j);
%        end
%        gIndex = gIndex +1;
%     end
%     typeCount = typeCount +1;
%     if(typeCount > 3)
%         typeCount = 1;
%     end
%    
% end
% 
% function out = getXYZvals(input)
%     count = 1;
%     outArray = zeros(1,9);
%     for j = 1:2:size(input)
%         outArray(count) = input(j);
%         count = count + 1;
%     end
%     out = outArray;
% end
% 
% 

% 
