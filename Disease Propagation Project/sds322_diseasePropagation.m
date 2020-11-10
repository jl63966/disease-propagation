%% SDS322 Disease Propagation

%mex main.cpp disease_propagation.cpp

n = 400000; %population size
d = 8; %disease duration (days)
r = 0.15; %transfer probability
i = [5,20,40]; %daily interactions

sick1 = main(n,d,r,i(1));
sick2 = main(n,d,r,i(2));
sick3 = main(n,d,r,i(3));

days = [length(sick1),length(sick2),length(sick3)];

plot(1:days(1),sick1,'-o',1:days(2),sick2,'-x',1:days(3),sick3,'-*')
legend([num2str(i(1)),' interactions'],num2str(i(2)),num2str(i(3)))
title(['Disease Propagation (pop. = ',num2str(n),', r = ',num2str(r),')'])
ylabel('Infection Cases')
xlabel('Days')