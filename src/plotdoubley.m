 %plot �Գ���
 %data=importdata('F:\VS_PRO\SCA\Cluster-basedMethod\result\div_random_nosort.txt');
 %for i= end
 %x=x(1:2:end);
 %w8=data(1,2:256);
 %w8=w8(1:2:end);
 %w64=data(280,2:256);
 %w64=w64(1:2:end);
 %plot(x,data(59,2:256),'k');
 % legend('q_1=64');
 %xlabel('q_1�²�ֵ');
 %ylabel('ƽ����ɢϵ��')
 %hold on;
 %plot(x,data(280,2:256),'k-*');
 %,x,w64,'k-*'
 %axis([-127,127,0.0,1.5]);

% % plot ��������
for i=1:255
  x(i)=i-128;
end
data=importdata('F:\VS_PRO\Experiment\result\AGT\AGT_hm_differW_10000_0.500000.txt');
 for i=1:255
     avr(i)=mean(data(i+1,:));
     variance(i)=var(data(i+1,:));
 end
 yyaxis left; % ������ߵ���
 plot(x,avr,'k-','LineWidth',1);
 title('');
 ylim([0,200])
 xlabel('��ʵq_1ȡֵ');
 ylabel('AGT'); % ����y���������ǩ
 
 yyaxis right; % �����ұߵ���
 plot(x,variance,'k-.','LineWidth',1.5);
 ylim([0,6000]) % ������y��Ľ���
 ylabel('VGT'); % ����y���������ǩ
 
 xlim([-128,128]);
 legend('AGT','VGT');

%set(gca,'xticklabel',{'HW','Random-1','Random-2','Random-3','Random-4'});
%data=importdata('F:\VS_PRO\Experiment\result\TOPK\differentModel\differModelall.txt');
%bar(data);
% applyhatch(gcf,'\-x.');
%

% data=importdata('F:\VS_PRO\Experiment\result\TOPK\NoiseInfluence_HW\TOPK_accuracy_hm_10000_0.0-1.0.txt');
% %data=importdata('F:\VS_PRO\Experiment\result\TOPK\SampleInfluence_HW\TOPK_accuracy_hm_1-100000_0.2.txt');
% for i=1:11
% x(i)=(i-1)*0.1;
% end
% plot(x,data(:,1)*100,'k-*','LineWidth',1);
% hold on;
% plot(x,data(:,2)*100,'k-x','LineWidth',1);
% hold on;
% plot(x,data(:,5)*100,'k-o','LineWidth',1);
% ylabel('TOPK�ָ���(%)');
% xlabel('��������');
% ylim([20,95]);
% legend('TOP1','TOP2','TOP5');
% data=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_1000_0.200000.txt');
% data1=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_2000_0.200000.txt');%
% data2=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_3000_0.200000.txt');
% data3=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_4000_0.200000.txt');
% data4=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_5000_0.200000.txt');
% data5=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_6000_0.200000.txt');
% data6=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_7000_0.200000.txt');
% data7=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_8000_0.200000.txt');
% % data8=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_9000_0.200000.txt');
% data9=importdata('F:\VS_PRO\Experiment\result\TOPK\TOPK_accuracy_hm_10000_0.200000.txt');
% for i=1:256
% x(i)=i;
% end
% %plot(x,data*100);
% % hold on;
% % plot(x,data1*100)
% % hold on;
% % plot(x,data2*100)
% % hold on;
% % plot(x,data3*100)
% % hold on;
% % plot(x,data4*100)
% % hold on;
% % plot(x,data5*100)
% % hold on;
% % plot(x,data6*100)
% % hold on;
% % plot(x,data7*100)
% % hold on;
% % plot(x,data8*100)
% % hold on;
% plot(x,data9*100,'k-')
% 
% ylabel('TOPK�ָ���(%)');
% xlabel('Kȡֵ');
% xlim([0,256]);
% ylim([20,100]);

% %plot M vs hole
% for i=1:100000
% m(i)=0.0000205175+i*0.00001;
% k(i)=floor(1/(256*m(i)))*2;
% logm(i)=log10(m(i));
% end
% plot(logm,k,'k');
% ylabel('�ն������С');
% xlabel('log_{10} M');
% xlim([-4.6,0]);
% ylim([0,270]);






%If you want to adjust the pattern to 6 bar such as " applyhatch(gcf,'.-+/|x');",
%try to type this "applyhatch(gcf,'.-++/||xx');" instedly. 
%So you can avoid the duplicated pattern at least, even order problem is still not solved. 
%data=[345,359,209;155,161,99];%���е���״ͼ����Ϊ�����֣������ͼ

%b=bar(data);%����״ͼ

%text(0.73,345+12,'345');%������״ͼ�ϵ���ֵ��С
%text(0.73+0.23,359+12,'359');
%text(0.73+0.45,209+12,'209');

%text(0.73+1,155+12,'155');
%text(0.73+1+0.23,161+12,'161');
%text(0.73+1+0.46,99+12,'99');

%grid on;%����������
%ch = get(b,'children');
%title('ʵ��2')
%set(gca,'XTickLabel',{'LINEITEM','ORDERS'})%����X����ʾ

%set(ch,'FaceVertexCData',[0 0 1;1 0 0;0 1 0])
%legend('����1','����2','����2');%����
%ylabel('ʱ��(�룩');%����y������
%applyhatch(gcf,'/\xx');%��ԭͼ������䣬�����и�bug����xx��Ҫ��������

