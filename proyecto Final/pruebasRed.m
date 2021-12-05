

digitDatasetPath=fullfile('grafi');
%digitDatasetPath=fullfile('imagenesmatlab');
imds=imageDatastore(digitDatasetPath,'IncludeSubfolders',true,'LabelSource','foldernames');

YPred=classify(net,imds);
YValidation=imds.Labels;
accuracy=mean(YPred==YValidation);
