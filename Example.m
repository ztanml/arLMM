% Example: Fitting an LMM on synthetically generate data

% Generate synthetic data
n = 1000; % 1000 observations
p = 100;  % 100 fixed effects
d = 3;    % 3 random effects
m = 20;   % observations correspond to 20 groups
alpha = 1;% for generating approximately the same #observations per group
[X,y,Z,Beta,H,s2] = genCusData(n,p,d,m,alpha);

disp('Fitting the LMM ...')
[estBeta,~,~,estH,ests2,cr] = arLMM(X,y,Z);

disp('Real vs estimated random-effect covariances:')
disp(H); disp(estH)
pause(3);
disp('[Real_noise_var  Estimated_noise_var]:')
disp([s2 ests2]);
pause(3);
disp(strcat("Corr(Real_Beta,Estimated_Beta):", num2str(corr(Beta,estBeta))));
